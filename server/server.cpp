#include "server.h"

string Server::readSocket(tcp::socket &socket) {
    streambuf buf;
    read_until(socket, buf, "\n");
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

void Server::sendSocket(tcp::socket &socket, const string &message) {
    string msg = message;
    if (msg.back() != '\n')
        msg += '\n';
    write(socket, buffer(msg));
}

void Server::startClientSession(const Server::socket_ptr &socket) {
    string message = readSocket(*socket);
    sendSocket(*socket, message);
    socket->close();
}

void Server::run() {
    tcp::acceptor acceptor(ioContext,
                           tcp::endpoint(ip::address::from_string(ip),
                                         port));
    while(true) {
        socket_ptr socket(new ip::tcp::socket(ioContext));
        acceptor.accept(*socket);
        boost::thread(boost::bind(startClientSession, socket));
    }
}

Server::Server(string ip, int port) : ip(ip), port(port) {}
