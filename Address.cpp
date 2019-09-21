#include "Address.h"
#include<ifaddrs.h>
#include<netdb.h>
#include<stddef.h>
using namespace std;
namespace miracle{
    Address::ptr Address::create(const sockaddr* addr,socklen_t len){
        if(addr==nullptr){
            return nullptr;
        }
        Addrss:ptr result;
        switch(addr->sa_family){
            case AF_INET:
                result.reset(new IPv4Address(*(sockaddr_in*)addr));
                break;
            case AF_INET6:
                break;
            default:
                break;
        }
        return result;
    }
    IPAddress::ptr IPAddress::create(const char* address,uint16_t port){
        addrinfo hints,*results;       
        memset(&hints,0,sizeof(addrinfo));

        hints.ai_flags = AI_NUMERICHOST;
        hints.ai_family=AF_UNSPEC;
        int error =getaddrinfo(address,NULL,&hints,&results);
        if(error){
            cout<< "IPAddress::create() error"<<endl;
            return nullptr;
        }
        try{
            IPAddress:ptr result =std::dynamic_pointer_cast<IPAddress>(Address::create(results->ai_addr,socklen_t(results->ai_addrlen)));
            if(result){
                result->setPort(port);
            }
            freeaddrinfo(results);
            return result;
        }catch(...){
            freeaddrinfo(results);
            return nullptr;
        }
    }
    int Address::getFamily() const{
        return getAddr()->sa_family;
    }
    IPv4Address::ptr IPv4Address::create(const char* address,uint16_t port){
        IPv4Address::ptr rt(new IPv4Address);
        rt->m_addr.sin_port=port;
        int result =inet_pton(AF_INET,address,&rt->m_addr.sin_addr);
        if(result<=0){
            return nullptr;
        }
        return rt;
    }
    const sockaddr* IPv4Address::getAddr() const{
        return (sockaddr*)&m_addr;
    }
    socklen_t IPv4Address::getAddrLen()const{
        return sizeof(m_addr);
    }
     uint32_t IPv4Address::getPort() const{
        return m_addr.sin_port;
    }

    void IPv4Address::setPort(uint16_t v){
        m_addr.sin_port=v;
    }

    IPv4Address::IPv4Address(const sockaddr_in& address){
        m_addr=address;
    }
    IPv4Address::IPv4Address(uint32_t address,uint16_t port){
        memset(&m_addr,0,sizeof(m_addr));
        m_addr.sin_addr.s_addr=address;
        m_addr.sin_port=port;
        m_addr.sin_family=AF_INET;
    }
    std::ostream& IPv4Address::insert(std::ostream& os)const{
        
    }
    bool Address::operator < (const Address& rhs)const{
        return true;
    }

    bool Address::operator == (const Address& rhs)const{
        return true;
    }
    bool Address::operator !=(const Address& rhs)const{
        return true;
    }

}
