#pragma once
#include "Connection.h"
#include <vector>
namespace StarryX {
	namespace Network {
		class Server : public Connection {
		public:
			enum class State {
				Closed,
				Listening
			};

			Server(Type ct = TCP) noexcept;
			~Server();

			/*
				����true����mg_connection�Ƿ񴴽���״̬����ͨ��
			*/
			bool Bind(const std::string& addr, uint16_t port);
			bool Bind(uint16_t port);

			/*
				Func:	TCP���ӷ�����Ϣ���һ�����Ϣͷ������uint32_t����ʾ����
				Param:	mgCon	������Ϣ�����ӣ�������ò����������������ӵĶ˷��͡�
				Desc:	mgCon��ʾ������һ��Ҫ�Ǹ�Server�����ӵģ������ܳɹ�����
			*/
			void Send(mg_connection* mgCon, const void* buff, size_t len) const;
			void Send(mg_connection* mgCon, const char* buff) const;
			void Send(mg_connection* mgCon, const std::string& str) const;
			void Send(mg_connection* mgCon, const Message& msg) const;
            inline void Send(const void* buff, size_t len) const {
                for (auto it = conVec.cbegin(); it != conVec.cend(); it++) {
                    Send(*it, buff, len);
                }
            };
            void Send(const char* buff) const {
                for (auto it = conVec.cbegin(); it != conVec.cend(); it++) {
                    Send(*it, buff);
                }
            };
            void Send(const std::string& str) const {
                for (auto it = conVec.cbegin(); it != conVec.cend(); it++) {
                    Send(*it, str);
                }
            };
            void Send(const Message& msg) const {
                for (auto it = conVec.cbegin(); it != conVec.cend(); it++) {
                    Send(*it, msg);
                }
            };

			/*
				�ر�Server
			*/
			void Close() const override;
			/*
				�ر�Server��ĳһ�����ӣ�mgCon��ʾ������һ��Ҫ�Ǹ�Server�����ӵ�
			*/
			void Close(mg_connection* mgCon) const;

			/*
				���ص�ǰ����״̬��
			*/
			State GetState() const noexcept { return cs; };

			/*
				����ȫ���Ե����ӡ�
			*/
			const std::vector<mg_connection*>& GetSockets() const noexcept { return conVec; };
		private:
			std::vector<mg_connection*> conVec = std::vector<mg_connection*>();
			State cs = State::Closed;
			static void MG_EventHandler(mg_connection* nc, int ev, void* ev_data);
		};
	};
};