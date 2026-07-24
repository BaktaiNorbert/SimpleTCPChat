#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include "thread"
#include "atomic"

struct Client
{
    int fd;
    std::string name;
    std::thread thread;
    std::atomic<bool> running{true};

    Client(int f, std::string n)
        : fd(f), name(std::move(n)) {}

    Client(Client&& other) noexcept
        : fd(other.fd),
        name(std::move(other.name)),
        thread(std::move(other.thread)),
        running(other.running.load())
    {}
};

#endif // CLIENT_H
