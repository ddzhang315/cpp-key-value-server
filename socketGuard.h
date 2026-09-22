#pragma once
#include<unistd.h>

class SocketGuard
{
    private:
        int fd;

    public:
        explicit SocketGuard(int fd):fd(fd){}

        ~SocketGuard()
        {
            if(fd >= 0)
            {
                close(fd);
            }
        }

        SocketGuard(const SocketGuard&) = delete;
        SocketGuard& operator=(const SocketGuard&) = delete;
};
