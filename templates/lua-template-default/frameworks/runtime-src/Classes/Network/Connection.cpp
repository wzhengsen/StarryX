#include "Connection.h"
#include <sstream>
using namespace StarryX::Network;

constexpr uint32_t Connection::MessageBuffer::InitMsgLen;
bool Connection::MessageBuffer::ParseData(const void* buff, size_t len) {
    // ����׷�ӵ�msgBuff��
	if (Append(buff, len)) {
		const uint32_t flagLen = *static_cast<const uint32_t*>(buffer);
		if (flagLen <= Message::MaxMsgLen && flagLen) {
			return true;
		}
        // ����Message::MaxMsgLen�����0��ͷ����Ϣ���Ϸ���
        size = 0;
	}
	return false;
}

bool Connection::MessageBuffer::Append(const void* src,size_t len) {
	if (!len || len + size > MaxMsgLen) {
        // ����Ϣ���ȳ��ޣ�����׷�ӣ�����ʧ�ܡ�
		return false;
	}
	if (len + size > capacity) {
        // ����ǰ�����������䣬������չ������
		while (capacity <= MaxMsgLen) {
            // ��������2����
			capacity *= 2;
			if (len + size <= capacity) {
                buffer = ::realloc(buffer, capacity);
				break;
			}
		}
	}
    // ��β��׷�ӡ�
	::memcpy(static_cast<uint8_t*>(buffer) + size, src, len);
	size += len;
	return true;
}

const void* Connection::MessageBuffer::GetData(size_t& len) const noexcept {
    len = GetLen();
    if (len) {
        return static_cast<uint8_t*>(buffer) + sizeof(uint32_t);
    }
    return nullptr;
}

uint32_t Connection::MessageBuffer::GetLen() const noexcept {
    if (size < sizeof(uint32_t)) {
        // ����δ�ﵽͷ����ʶ������ֽ�����
        return 0;
    }
    const uint32_t flagLen = *reinterpret_cast<const uint32_t*>(buffer);
    if (!flagLen || flagLen > size - sizeof(uint32_t) || flagLen > size) {
        // ͷ����ʶ����Ϊ0����ڳ��ȡ�
        return 0;
    }
    return flagLen;
}

void Connection::MessageBuffer::Cut(size_t len) noexcept {
	if (size < len + sizeof(uint32_t)) {
        size = 0;
		return;
	}
	::memmove(buffer, static_cast<uint8_t*>(buffer) + len + sizeof(uint32_t), size - len - sizeof(uint32_t));
	size -= (len + sizeof(uint32_t));
}

Connection::MessageBuffer::MessageBuffer(size_t initSize) noexcept {
    buffer = ::malloc(initSize);
	capacity = initSize;
}

Connection::MessageBuffer::~MessageBuffer() {
	if (buffer) {
		::free(buffer);
		buffer = nullptr;
	}
}

constexpr char Connection::UDP_Header[];
constexpr char Connection::TCP_Header[];
size_t Connection::activeCount = 0;
mg_mgr* Connection::mgMgr = nullptr;
std::map<const mg_connection*, Connection::MessageBuffer> Connection::mgBuffMap = std::map<const mg_connection*, Connection::MessageBuffer>();

Connection::Connection(Type ct) noexcept : ct(ct) {
    activeCount++;
}

Connection::~Connection() {
    activeCount--;
	Close();
	if (mgCon) {
		if (!(mgCon->flags & MG_F_UDP)) {
			mgBuffMap.erase(mgCon);
		}
		mgCon->user_data = nullptr;
	}

	SetHandler(nullptr);
}

void Connection::InitConnection(const std::string& addr, uint16_t port) {
	this->addr = addr;
	this->port = port;

	auto sString = std::stringstream();
	sString << port;

	//���UPD��TCPͷ
	connAddr = (ct == TCP ? TCP_Header : UDP_Header) + addr + ":" + sString.str();
    if (!mgMgr) {
        mgMgr = static_cast<mg_mgr*>(::malloc(sizeof(mg_mgr)));
        mg_mgr_init(mgMgr, nullptr);
    }
}

void Connection::Close() const {
	if (mgCon) {
		mgCon->flags |= MG_F_CLOSE_IMMEDIATELY;
	}
    if (!activeCount) {
        CloseMGR();
    }
}

void Connection::CloseMGR() noexcept {
    if (!mgMgr) {
        return;
    }
	mg_mgr_free(mgMgr);
	mgMgr = nullptr;
}

void Connection::Poll() noexcept {
	if (!mgMgr) {
		return;
	}
	mg_mgr_poll(mgMgr, 0);
}

void Connection::MG_EventHandler(mg_connection* nc, int ev, void* ev_data) {
	switch(ev){
	case MG_EV_POLL:
		break;
	case MG_EV_RECV: {
		auto conn = static_cast<Connection*>(nc->user_data);
		if (conn && conn->eventHandler) {
			const char* buf = nc->recv_mbuf.buf;
			auto len = nc->recv_mbuf.len;

			if (nc->flags & MG_F_UDP) {
				if (!len || len > Message::MaxMsgLen) {
					//��������Ϣ���Ϸ�ʱ��رո�����
					conn->mgCon->flags |= MG_F_CLOSE_IMMEDIATELY;
					nc->flags |= MG_F_CLOSE_IMMEDIATELY;
					mbuf_remove(&nc->recv_mbuf, nc->recv_mbuf.len);
					return;
				}
                auto info = Info();
				info.event = static_cast<Event>(ev);
				info.conn = nc;
				info.msg->Resize(len);
                ::memcpy(info.msg->GetBuff(), buf, len);
				conn->eventHandler(conn, &info);
			}
			else {
                auto iter = mgBuffMap.find(nc);
                if (iter != mgBuffMap.end()) {
                    const auto ret = iter->second.ParseData(buf, len);
                    if (!ret) {
                        //��������Ϣ���Ϸ�ʱ��رո�����
                        nc->flags |= MG_F_CLOSE_IMMEDIATELY;
                        mbuf_remove(&nc->recv_mbuf, nc->recv_mbuf.len);
                        iter->second.Clear();
                        return;
                    }

                    size_t msgLen = 0;
                    do {
                        const void* msgBuff = iter->second.GetData(msgLen);

                        if (msgLen) {
                            auto info = Info();
							info.event = static_cast<Event>(ev);
							info.conn = nc;
							info.msg->Resize(msgLen);
                            ::memcpy(info.msg->GetBuff(), msgBuff, msgLen);
                            iter->second.Cut(msgLen);
							conn->eventHandler(conn, &info);
                        }
                    } while (msgLen);
                }
				else {
					nc->flags |= MG_F_CLOSE_IMMEDIATELY;
					mbuf_remove(&nc->recv_mbuf, nc->recv_mbuf.len);
					return;
				}
			}
		}
		//�Ƴ����ջ���
		mbuf_remove(&nc->recv_mbuf, nc->recv_mbuf.len);
		break;
	}
	default:
		break;
	}
}
