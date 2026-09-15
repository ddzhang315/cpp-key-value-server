#pragma once
#include "commandParser.h"
#include "keyValueStore.h"
#include <string>

std::string executeCommand(const ParsedCommand& command, KeyValueStore& store);