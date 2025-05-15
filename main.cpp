#include "server.h"

int main(int argc, char* argv[]) 
{
    int port = DEFAULT_PORT;
    if (argc > 1) {
        port = std::stoi(argv[1]); 
    }
    start_server(port);  
    return 0;
}
