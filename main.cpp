#include <iostream>
#include "keyValueStore.h"
#include <cassert>
#include <sstream>
#include <string>


int main()
{

    std::cout<< "C++ Key Value Server" << std::endl;

    KeyValueStore kv;
    std::string input;
    std::string command;
    std::string key;
    std::string value;
    std::string extra;

    while(std::getline(std::cin, input))
    {
        std::istringstream iss(input);

        if(!(iss >> command))
        {
            continue;
        }

        if(command == "SET")
        {
            if(!(iss >> key >> value))
            {
                std::cout << "Usage: SET key value\n";

            }else if(iss>>extra)
            {
               std::cout << "Too many arguments. Usage: SET key value\n";
            }else{
                kv.set(key,value);
                std::cout <<"Set success!\n";  
            }
            
        }else if(command == "GET")
        {
            if(!(iss >> key))
            {
                std::cout << "Usage: GET key\n";
            }else if(iss >> extra)
            {
                 std::cout << "Too many arguments. Usage: GET key\n";
            }else
            {
                auto res = kv.get(key);
                if(res)
                {
                    std::cout << *res << std::endl;
                }else{
                    std::cout << "Item Not Found!\n";
                }
            }
        }else if (command == "DELETE")
        {
            if(!(iss>>key))
            {
                std::cout << "Usage: DELETE key\n";
            }else if(iss >> extra)
            {
                std::cout << "Too many arguments. Usage: DELETE key\n";
            }else
            {
                if(kv.remove(key))
                {
                    std::cout <<"DELETE success!\n";
                }else
                {
                    std::cout<< "Item Not found!\n";
                }
            }
        }else if(command == "Q")
        {
            if(iss >> extra)
            {
                std::cout << "Too many arguments. Usage: Q\n";
            }else
            {
                std::cout<<"Quit success!\n";
                break;
            } 
        }else
        {
             std::cout <<" Please provide a valid command from [GET,SET,DELETE or Q]\n";
        }
    }

    return 0;
}