#include <iostream>
#include "keyValueStore.h"
#include "commandParser.h"
#include "tcpServer.h"
#include <string>


int main()
{

    std::cout<< "C++ Key Value Server" << std::endl;

    runServer();

    return 0;
}
