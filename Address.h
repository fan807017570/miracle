#ifndef __MIRACLE__ADDRESS_H_
#define __MIRACLE__ADDRESS_H_
#include<memory>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<vector>
#include<map>

namespace miracle{
    class IPAddress;
    class Address{
        public:
            typedef std::shared_ptr<Address> ptr;
            static Address::ptr create(const sockaddr* addr,socklen_t len);
            virtual ~Address(){}
            int getFamily() const;
            virtual const sockaddr* getAddr() const =0;
            virtual socklen_t getAddrLen()const =0;
            virtual std::ostream& insert(std::ostream& os)const =0;
            std:string toString() const;
            bool operator< (const Address& rhs)const;
            bool operator==(const Address& rhs)const;
            bool operator!=(const Address& rhs)const;
    };
    class IPAddress:public Address{
        public:
            typedef shared_ptr<IPAddress> ptr;
            static IPAddress::ptr create(const char* address,uint16_t port=0);
            virtual uint32_t getPort() const =0;
            virtual void setPort(uint32_t v)=0;
            
    };
    class IPv4Address:public IPAddress{
        public:
            typedef shared_ptr<IPv4Address> ptr;
            static IPv4Address::ptr create(const char* address,uint16_t port=0);
            IPv4Address(const sockaddr_in& address);    
            IPv4Address(uint32_t address=INADDR_ANY,uint16_t port=0)
    };
}
#endif
