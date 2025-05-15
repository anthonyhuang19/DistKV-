// server.cpp
#include "server.h"
#include "storage.h"
#include "replica.h"

#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void handle_client(int client_socket) 
{
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    
    if (bytes_received <= 0) 
    {
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    std::string request(buffer);
    std::istringstream iss(request);
    std::string command, key, value;
    iss >> command >> key; // split the req to command and key

    std::string response;

    if (command == "SET") {
        iss >> value;
        set_value(key, value);                     // Simpan ke store
        replicate_to_replicas(request);            // Replikasi ke node lain
        response = "OK\n";
    } 
    else if (command == "GET") 
    {
        response = get_value(key);
    } 
    else 
    {
        response = "INVALID_COMMAND\n";
    }

    send(client_socket, response.c_str(), response.length(), 0);
    close(client_socket);
}

void start_server(int port) 
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);
    std::cout << "Server started on port " << port << std::endl;

    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        std::thread(handle_client, client_socket).detach();  // Tangani tiap client di thread terpisah
    }
}
