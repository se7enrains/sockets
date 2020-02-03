//
// Created by se7enrains on 1/31/20.
//

#include "client.h"

Client::Client(string ip, int port) : ip(std::move(ip)), port(port) {
}

string Client::readSocket(tcp::socket &socket) {
    streambuf buf;
    read_until(socket, buf, "\n", error);
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

void Client::sendSocket(tcp::socket &socket, const string &message) {
    string msg = message;
    if (msg.back() != '\n')
        msg += '\n';
    write(socket, buffer(msg), error);
}

void Client::run() {
    tcp::socket socket(ioContext);
    socket.connect(tcp::endpoint(
            ip::address::from_string(ip), port), error);
    if (error){
        std::cerr << "Connection failed: " << error.message() << std::endl;
        return;
    }
    std::string message;
    std::cout << "Enter message: ";
    std::getline(std::cin, message, '\n');
    message.append("\n");
    sendSocket(socket, message);
    if (!error) {
        std::cout << "Client sent: " << message;
    } else {
        std::cerr << "Send failed: " << error.message() << std::endl;
        return;
    }
    string receivedMessage = readSocket(socket);
    if (error && error != error::eof) {
        std::cerr << "Receive failed: " << error.message() << std::endl;
        return;
    }
    else{
        std::cout << "Received: " << receivedMessage << std::endl;
        if (message == receivedMessage)
            std::cout << "Messages are equal" << std::endl;
    }
}
