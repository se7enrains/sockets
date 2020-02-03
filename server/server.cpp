#include "server.h"

string Server::readSocket(tcp::socket &socket) {
    streambuf buf;
    boost::system::error_code error;
    read_until(socket, buf, "\n", error);
    if (error && error != error::eof){
        std::cerr << "Read error: " << error.message() << std::endl;
        return "Server couldn't read message\n";
    }
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

void Server::sendSocket(tcp::socket &socket, const string &message) {
    string msg = message;
    if (msg.back() != '\n')
        msg += '\n';
    boost::system::error_code error;
    write(socket, buffer(msg), error);
    if (error){
        std::cerr << "Send error: " << error.message() << std::endl;
    }
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
        boost::thread(&Server::startClientSession, this, socket);
    }
}

Server::Server(string ip, int port) : ip(std::move(ip)), port(port) {}
