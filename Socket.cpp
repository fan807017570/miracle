#include "Socket.h"
namespace miracle{
    Socket::ptr Socket::createTCP(Address::ptr address){
        
    }
    Socket::ptr Socket::createUDP(Address::ptr address){
        
    }
    Socket::ptr Socket::createTCPSocket(){
    }
    Socket::ptr Socket::createUDPSocket(){
    }
    Socket::ptr Socket::createUnixUDPSocket(){
    }
    bool Socket::getOption(int level,int option,void* result,socklen_t len){
    }
    bool Socket::setOption(int level,int option,void* result,socklen_t len){
    }
    Address::ptr Socket::getRemoteAddress(){
    }
    Address::ptr Socket::getLocalAddress(){
    }
    Socket::Socket(int family,int type,int protocol):
    m_sock(-1)
    ,m_family(family)
    ,m_type(type)
    ,m_protocol(protocol)
    ,m_isconnected(false)
    {}
}
