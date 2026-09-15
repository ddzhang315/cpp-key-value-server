#include "commandExecutor.h"


std::string executeCommand(const ParsedCommand& command, KeyValueStore& store)
{
    if(command.command == "SET")
    {
        store.set(command.key,command.value);
        return "Set success!";  
        
    }else if(command.command == "GET")
    {
        auto res = store.get(command.key);
        if(res)
        {
            return *res;
        }else{
            return "Item Not Found!";
        }
        
    }else if (command.command == "DELETE")
    {
        
        if(store.remove(command.key))
        {
            return "DELETE success!";
        }else
        {
            return "Item Not Found!";
        }
        
    }else if(command.command == "CONTAINS")
    {
        if(store.contains(command.key))
        {
            return "Key exists!";
        }else{
            return "Key does not exist!";
        }
    }else if(command.command == "SIZE")
    {
        return "Size is : " + std::to_string(store.size());
    }

    return "Unkown Command";
}