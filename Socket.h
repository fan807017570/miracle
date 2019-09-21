#ifndef __MIRACLE_SOCKET_H_
#define __MIRACLE_SOCKET_H_

#include<memory>
#include"Address.h"
#include<sys/socket.h>
#include<sys/types.h>
#define SOMAXCONN 10
namespace miracle{
    class Socket:public std::enable_shared_from_this<Socket>,Noncopyable{
        public:
            typedef std::shared_ptr<Socket> ptr;
            typedef std::weak_ptr<Socket> weak_ptr;
            enum type{
                TCP=SOCK_STREAM,
                UDP=SOCK_DGRAM
            };
            enum Family{
                IPv4=AF_INET,
                IPv6=AF_INET6,
                UNIX=AF_UNIX
            };  
            static Socket::ptr createTCP(Address::ptr address);
            static Socket::ptr createUDP(Address::ptr address);
            static Socket::ptr createTCPSocket();
            static Socket::ptr createUDPSocket();
            static Socket::ptr createUnixUDPSocket();
            bool getOption(int level,int option,void* result,socklen_t len);
            bool setOption(int level,int option,const void* result,socklen_t len);
            virtual ~Socket();

            virtual Socket::ptr accept();

            virtual bool bind(const Address::ptr addr);
            virtual bool connect(cosnt Address::ptr addr,uint64_t timeout_ms =-1);
            virtual bool listen(int backlog =SOMAXCONN);
            virtual bool close();
            virtual int send(const void* buffer,size_t len,int flags=0);
            virtual recv(void* buffer,size_t len,int flags=0);
            Address::ptr getRemoteAddress();
            Address::ptr getLocalAddress();
            Socket(int fimaly,int type,int protocol=0);
            int getFamily() const {return m_family;}
            int geType()const {return m_type;}
            int getProtocol() const {return m_protocol;}
            int isConnected() const {return m_isconnected;}
            int getSock() const {return m_sock;}
            private:
                int m_sock;

                int m_family

                int m_type;

                int m_protocol;

                bool m_isconnected;

                Address::ptr m_localAddress;
                Address::ptr m_remoteAddress;
            protected:
                void initSock();
                void newSock();
                virtual bool init(int sock);
    };
    std::ostream& opreator<< (std::ostream& os,const Socket& socket);
}
#endif
