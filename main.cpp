#include <iostream>
#include "keyValueStore.h"
#include "commandParser.h"
#include "tcpServer.h"
#include <string>


int main()
{

    std::cout<< "C++ Key Value Server" << std::endl;

    KeyValueStore kv;
    runServer(kv);
    /*
    std::string input;

    while(std::getline(std::cin, input))
    {
        ParsedCommand pc = parseCommand(input);

        if(!pc.error.empty())
        {
            std::cout << pc.error <<'\n';
            continue;
        }


        if(pc.command == "SET")
        {
            
            kv.set(pc.key,pc.value);
            std::cout <<"Set success!\n";  
            
        }else if(pc.command == "GET")
        {
            
            auto res = kv.get(pc.key);
            if(res)
            {
                std::cout << *res << std::endl;
            }else{
                std::cout << "Item Not Found!\n";
            }
            
        }else if (pc.command == "DELETE")
        {
           
            
            if(kv.remove(pc.key))
            {
                std::cout <<"DELETE success!\n";
            }else
            {
                std::cout<< "Item Not Found!\n";
            }
            
        }else if(pc.command == "CONTAINS")
        {
            if(kv.contains(pc.key))
            {
                std::cout <<"Key exists!\n";
            }else{
                std::cout << "Key does not exist!\n";
            }
        }else if(pc.command == "SIZE")
        {
            std::cout << "Size is : " << kv.size() << "\n";
        }else if(pc.command == "Q")
        {
            
            std::cout<<"Quit success!\n";
            break;
        }
    }
        */

    return 0;
}