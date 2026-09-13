#pragma once
#include <string>

struct ParsedCommand
{
    std::string command;
    std::string key;
    std::string value;
    std::string error;
};

ParsedCommand parseCommand(const std::string& input);