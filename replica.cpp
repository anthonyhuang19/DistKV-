#include "replica.h"

#include<vector>
#include<string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

vector<string> replica_ips ={"127.0.0.1"};
int replica_port = 9001;

void replicate_to_replicas(const std:: string & command)
{
    for (const auto & ip : replica_ips)
    {
        int sock = socket(AF_INET,SOCK_STREAM,0); // making tcp socket
        if (sock < 0) continue;


        sockaddr_in replica_addr{};
        replica_addr.sin_family = AF_INET; 
        replica_addr.sin_port = htons(replica_port);
        inet_pton(AF_INET, ip.c_str(), &replica_addr.sin_addr); // convert ip to binary
        
        if (connect(sock, (sockaddr*)&replica_addr, sizeof(replica_addr)) == 0) 
        {  
            send(sock, command.c_str(), command.length(), 0); 
        }
        close(sock);  
    }
}