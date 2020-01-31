#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;
using std::string;

class Server {
private:
    io_context ioContext;
    string ip;
    int port;
    typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
    static string readSocket(tcp::socket &socket);
    static void sendSocket(tcp::socket &socket, const string &message);
    static void startClientSession(const socket_ptr& socket);
public:
    Server(string ip, int port);
    void run();
};

#endif //SERVER_SERVER_H
