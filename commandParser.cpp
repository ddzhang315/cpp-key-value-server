#include "commandParser.h"
#include <sstream>

ParsedCommand parseCommand(const std::string& input)
{
    ParsedCommand result;
    std::istringstream iss(input);
    std::string extra;

    if(!(iss >> result.command))
    {
        result.error ="Error: Empty command!";
        return result;
    }

    if(result.command == "SET")
    {
        if(!(iss >> result.key >> result.value))
        {
            result.error = "Error: (Usage: SET key value)";
            return result;
        }

        if(iss >> extra)
        {
            result.error = "Error: (Too many arguments. Usage: SET key value)";
            return result;
        }
    }else if(result.command == "GET")
    {
         if(!(iss >> result.key))
        {
            result.error = "Error:(Usage: GET key)";
            return result;
        }

        if(iss >> extra)
        {
            result.error = "Error:(Too many arguments. Usage: GET key.)";
            return result;
        }

    }else if(result.command == "DELETE")
    {
        if(!(iss >> result.key))
        {
            result.error = "Error:(Usage: DELETE key)";
            return result;
        }

        if(iss >> extra)
        {
            result.error = "Error:(Too many arguments. Usage: DELETE key.)";
            return result;
        }

    }else if(result.command == "Q")
    {
        if(iss >> extra)
        {
            result.error = "Error: (Too many arguments. Usage: Q (to quit).)";
            return result;
        }

    }else{
        
        result.error ="Error: (Invalid command. Please provide a valid command from [GET,SET,DELETE or Q])";
        return result;
    }
    return result;

}