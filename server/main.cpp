#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;

string readSocket(tcp::socket &socket){
    streambuf buf;
    read_until(socket, buf, "\n");
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

void sendSocket(tcp::socket &socket, const string &message){
    string msg = message;
    if (msg.back() != '\n')
        msg += '\n';
    write(socket, buffer(msg));
}

int main() {
    io_service ioService;
    tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 61324));
    tcp::socket  socket(ioService);
    string promptResult;
    bool continueFlag = true;
    while (continueFlag) {
        acceptor.accept(socket);
        string message = readSocket(socket);
        std::cout << "Got message: " << message << std::endl;
        sendSocket(socket, message);
        socket.close();

        std::cout << "Continue listening? [Y/N]" << std::endl;
        std::cin >> promptResult;
        continueFlag = promptResult == "Y";
    }
    std::cout << "Finishing work" << std::endl;

    return 0;
}
