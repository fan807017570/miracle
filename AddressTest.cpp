#include"Address.h"
using namespace std;
using namespace miracle;
int main(){
    uint16_t port =8080;
    IPv4Address::ptr aptr=IPv4Address::create("127.0.0.1",port);    
    string ip(aptr->getAddr()->sa_data);
    cout<<ip<<endl;
    return 0;
}
