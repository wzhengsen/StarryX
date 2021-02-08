#pragma once
#include "mongoose/mongoose.h"
#include <string>
#include <map>
#include <functional>
namespace StarryX {
	namespace Network {
		/*
		����mongoose�����װ
		*/
		class Connection {
        private:
            struct MgrWrapper;
		public:
			struct MessageBuffer;
			/*
				��Ϣ�ṹ
				���е��շ���Ϣ��Ӧ��ѭ�˽ṹ��
                ÿһ�����Ӷ�����һ����Ӧ��MessageBuffer�������յ������ݣ���󳤶�Message::MaxMsgLen����Ч�ĳ��Ƚ��������ӹر�
                ÿһ����Ч���ݱض���Ҫ��uint32_t��ͷ��ָʾ���������ȣ��ɲ�������޷���ȫ���������ݽ��ݴ���MessageBuffer
			*/
			struct Message final {
				//�����Ϣ���ȣ������˳��ȿ��ܵ������ӱ������ر�
				static constexpr uint32_t MaxMsgLen = uint16_t(~0) + 1;

                inline Message() = default;

                inline Message(uint32_t len) noexcept {
                    this->len = len;
                    buff = ::malloc(len);
                }

                inline ~Message() {
                    if (buff) {
                        ::free(buff);
                        buff = nullptr;
                    }
                }

                inline void Resize(size_t len) noexcept {
                    this->len = len;
                    buff = ::realloc(buff, len);
                }

                inline Message(Message&& m) noexcept {
                    std::swap(len, m.len);
                    std::swap(buff, m.buff);
                }

                inline Message(const Message& m) noexcept {
                    len = m.len;
                    if (len) {
                        buff = ::malloc(len);
                        ::memcpy(buff, m.buff, len);
                    }
                }

                inline Message& operator=(const Message& m) noexcept {
                    if (buff) {
                        ::free(buff);
                    }
                    len = m.len;
                    if (len) {
                        buff = ::malloc(len);
                        ::memcpy(buff, m.buff, len);
                    }
                    return *this;
                }

                inline uint32_t GetLen() const noexcept {
                    return static_cast<uint32_t>(len);
                }

                inline void* GetBuff() const noexcept {
                    return buff;
                }

            private:
                //��Ϣ����
                size_t len = 0;
                //��ʵ��Ϣ�ײ�ָ��
                void* buff = nullptr;
			};

			/*
				������Ϣ���壬��󻺳�ΪMessage::MaxMsgLen
			*/
			struct MessageBuffer final {
			public:
				MessageBuffer(size_t initSize = InitMsgLen) noexcept;
				~MessageBuffer();

                /*
                    Desc:   ������������ȣ���δ��ջ�������
                */
                inline void Clear() noexcept {
                    size = 0;
                }

                /*
                    Desc:	��buff�н�����Ϣ������Ϣ�Ϸ���������뻺������
                    Param:	buff:	��Ϣ�����׵�ַ��
                            len:	��Ϣ���ݳ��ȡ�
                    Return:	�Ƿ�Ϸ�������
                */
                bool ParseData(const void* buff, size_t len);

                /*
                    Desc:   ��ͷ�����ָ�����ȵĻ�������������ʣ��Ļ�����ǰ�ơ�
                    Param:  len     ����������ĳ��ȡ�
                */
                void Cut(size_t len) noexcept;

                /*
                    Desc:	�ӻ������ж�ȡ��Ϣ������Ϣ�ṹ�Ϸ���4�ֽ�ָʾ���ȵ�ͷ��+�㹻��������������
                            �򽫷���ָ�����ڴ������ڴ�����Сͨ��ReadLen()��ȡ��
                    Param:  len         ��ȡ���ݳ��ȡ�
                    Return: ��������ָ��.
                */
                const void* GetData(size_t& len) const noexcept;

                static constexpr uint32_t InitMsgLen = 512;
			private:
				size_t capacity = InitMsgLen;
				size_t size = 0;
				void* buffer = nullptr;
                static constexpr uint32_t MaxMsgLen = Message::MaxMsgLen;

                /*
                    Desc:   ��һ���ڴ�����׷�ӵ��ڲ�������ĩβ��
                    Param:	src         �ڴ�������ָ�롣
                            len         ���ݳ��ȡ�
                    Return: ��������������MaxMsgLen���·���false,���򷵻�true
                */
                bool Append(const void* src, size_t len);

                /*
                    Desc:	��ȡ��һ����Ч��Ϣ�ĳ��ȣ���������Ϣͷ����4���ֽڡ�
                    Return:	��Ч���������ȡ�
                            ����0��ʾ��Ϣ���Ϸ���δ�ﵽ�ɶ�ȡ�ĳ��ȡ�
                */
                uint32_t GetLen() const noexcept;
			};

			/*
				�����¼�
			*/
			enum Event {
				MG_Poll = MG_EV_POLL,			/* Sent to each connection on each mg_mgr_poll() call */
				MG_Accept = MG_EV_ACCEPT,		/* New connection accepted. union socket_address * */
				MG_Connect = MG_EV_CONNECT,	/* connect() succeeded or failed. int *  */
				MG_Recv = MG_EV_RECV,			/* Data has been received. int *num_bytes */
				MG_Close = MG_EV_CLOSE,		/* Connection is closed. NULL */
				MG_Timer = MG_EV_TIMER,		/* now >= conn->ev_timer_time. double * */

				MG_None = 9999
			};

			enum Type {
				TCP,//Ĭ��
				UDP
			};

			/*
				���ڻص�����
			*/
			struct Info final {
				/*
					MG_Poll/MG_Timer���ڲ����������ڻص��м�����
					MG_Accept/MG_Connect/MG_Recv/MG_Send/MG_Close�����ڻص��м�����
				*/
				Event event = MG_None;

				const mg_connection* conn = nullptr;

                /*
                    MG_Recv�¼�ʱ�����ֶβ�������
                */
                Message* msg = nullptr;

                /*
                    MG_Connectʧ��ʱ�����ֶ�Ϊfalse
                */
                bool suc = false;

                /*
                    MG_Accpet�¼�ʱ����ֵΪ��ַ�Ͷ˿ڡ�
                */
                std::string addr = std::string();
                uint16_t port = 0;

                inline Info() noexcept {
                    msg = new Message();
                }

                inline ~Info() {
                    if (msg) {
                        delete msg;
                    }
                }
			};

			/*
				�ص�����ԭ��
			*/
            typedef std::function<void(const Connection* conn, const Info* eventInfo)> EventHandler;

			virtual ~Connection();
			Connection(const Connection&) = delete;
			Connection& operator=(const Connection&) = delete;

			virtual void Close() const;

			/*
				Ϊÿ���������ö������¼���Ӧ
			*/
            void SetHandler(EventHandler eh) noexcept {
                eventHandler = eh;
            }
            inline EventHandler GetHandler() const noexcept {
                return eventHandler;
            }
            inline Type GetType() const noexcept {
                return ct;
            }
            inline const mg_connection* GetConnection() const noexcept { return mgCon; };

            /*
                ֱ������ mg_mgr���˲�����ͬʱ�������е����Ӻ�socket
            */
            static void CloseMGR() noexcept;
            static void Poll() noexcept;
		protected:
			Connection(Type ct = TCP) noexcept;

            void InitConnection(const std::string& addr, uint16_t port);
			std::string connAddr = "";
			mg_connection* mgCon = nullptr;
			EventHandler eventHandler = nullptr;

			Type ct = Type::TCP;
            static mg_mgr* mgMgr;
			static std::map<const mg_connection*, MessageBuffer> mgBuffMap;

			/*
				mongoose�ص�
			*/
			static void MG_EventHandler(mg_connection* nc, int ev, void* ev_data);
		private:
			std::string addr = "";
            uint16_t port = 0;

			static constexpr char UDP_Header[] = "udp://";
			static constexpr char TCP_Header[] = "tcp://";

            static size_t activeCount;
		};
	};
};