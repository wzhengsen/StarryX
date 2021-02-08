#pragma once
#include "Connection.h"
namespace StarryX {
	namespace Network {

		class Client : public Connection {
			/*
				�򵥵Ŀͻ���ʵ��
			*/
		public:
			enum class State {
				Closed,
				Connecting,
				Connected
			};

			Client(Type ct = TCP) noexcept;

			/*
				����true������mg_connection�Ƿ񴴽���״̬����ͨ��������ʾ�ɹ�����
			*/
			bool Connect(const std::string& addr, uint16_t port, bool broadcast = false, uint32_t timeout = ConnectTimeout);

			/*
				TCP���ӻ�����Ϣͷ������uint32_t����ʾ����
			*/
			void Send(const void* buff, size_t len) const noexcept;
			void Send(const char* buff) const noexcept;
			void Send(const std::string& str) const noexcept;
			void Send(const Message& msg) const noexcept;

			/*
				���ص�ǰ����״̬��
			*/
			State GetState() const noexcept { return cs; };
		private:
			State cs = State::Closed;
			static void MG_EventHandler(mg_connection* nc, int ev, void* ev_data);
			/*
				�����¼���ʱ��������������ʱ�䣬�Զ��Ͽ�����
			*/
			static constexpr uint32_t ConnectTimeout = 5000;
		};
	};
};