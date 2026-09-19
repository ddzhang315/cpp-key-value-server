#include "tcpServer.h"
#include <sys/socket.h> // socket()
#include <unistd.h> // close()
#include <cstdio> //std::perror()
#include <iostream>
#include <netinet/in.h>
#include <cerrno>
#include "commandParser.h"
#include "commandExecutor.h"
#include "threadPool.h"


bool sendAll(int client_fd, const std::string& message)
{
    std::size_t total_sent = 0;

    while(total_sent < message.size())
    {
        ssize_t sent = send(client_fd, 
            message.data()+total_sent, 
            message.size()-total_sent,MSG_NOSIGNAL);

        if(sent == -1)
        {
            if(errno == EINTR)
            {
                continue;
            }

            std::perror("send");
            return false;
        }

        if(sent == 0)
        {
            return false;
        }

        total_sent += static_cast<std::size_t> (sent);
    }
    std::cout<< "sent success!\n";
    return true;
}

void handleClient(int client_fd, KeyValueStore& store)
{
    bool exit_flag = false;
    char buff[1024];
    std::string line;
    while(true)
    {
        ssize_t n = recv(client_fd, buff, sizeof(buff), 0);
        if(n==-1)
        {
            if(errno == EINTR) continue;
            std::perror("recv");
            return;
        }

        if(n==0)
        {
            std::cout << "Client disconnected!\n";
            return;
        }

        line.append(buff,static_cast<std::size_t>(n));
        std::size_t newline_pos;

        while((newline_pos=line.find('\n'))!= std::string::npos)
        {
            std::string command = line.substr(0, newline_pos);
            line.erase(0, newline_pos+1);
            std::cout << "one complete command: "<< command << std::endl;

            ParsedCommand pc = parseCommand(command);
            std::string response ="Server Response: ";

            if(!pc.error.empty())
            {
                response += pc.error;
                
            }else if(pc.command == "Q")
            {
                response += "GoodBye";
                exit_flag=true;
            }else{
                response += executeCommand(pc, store); 
            }

            response +="\n";
            
            if(!sendAll(client_fd, response))
            {
                std::cout << "response sent failed!\n";
                return;
            }

            if(exit_flag) return;
        }
    }
} 

int runServer()
{
    int server_fd = socket(AF_INET, SOCK_STREAM,0);

    if(server_fd == -1)
    {
        std::perror("socket");
        return 1;
    }

    std::cout << "Socket created successfully!\n";

    //configure the server address
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //bind to the configured address
    if(bind(server_fd, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) == -1)
    {
        std::perror("bind failed.");
        close(server_fd);
        return 1;
    }

    if(listen(server_fd,10)==-1)
    {
        std::perror("listen failed");
        close(server_fd);
        return 1;
    }

    std::cout << "Listening on 127.0.0.1:8080\n";

    KeyValueStore store;
    ThreadPool pool{4};

    while(true)
    {
        std::cout <<"Server is running and waiting for a new client...\n";
        int client_fd = accept(server_fd,nullptr,nullptr);
        if(client_fd == -1)
        {
            if(errno == EINTR)
            {
                continue;//interrupted by a signal; retry
            }
            std::perror("accept failed");
            break;
        }

        std::cout << "Client connected!\n";
       
        pool.enqueue([client_fd,&store]()
        {
            handleClient(client_fd,store);
            close(client_fd);
        });
    }
    
    close(server_fd);

    return 0;
}

