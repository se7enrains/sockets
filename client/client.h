#ifndef SOCKETS_CLIENT_H
#define SOCKETS_CLIENT_H
#include <boost/asio.hpp>
#include <iostream>
#include <utility>

using namespace boost::asio;
using ip::tcp;
using std::string;

class Client {
private:
    io_context ioContext;
    string ip;
    int port;
    boost::system::error_code error;
    string readSocket(tcp::socket &socket);
    void sendSocket(tcp::socket &socket, const string &message);
public:
    Client(string ip, int port);
    void run();
};

#endif //SOCKETS_CLIENT_H
