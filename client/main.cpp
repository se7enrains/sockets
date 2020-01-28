#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;


int main() {
    boost::asio::io_service ioService;
    tcp::socket socket(ioService);
    socket.connect(tcp::endpoint(
            ip::address::from_string("127.0.0.1"), 61324));
    std::string message;
    std::cout << "Enter message: ";
    std::getline(std::cin, message, '\n');
    message.append("\n");
    boost::system::error_code error;
    write(socket, buffer(message), error);
    if (!error)
        std::cout << "Client sent: " << message;
    else
        std::cout << "Send failed" << std::endl;
    streambuf receive_buffer;
    read_until(socket, receive_buffer,'\n');
    if (error && error != error::eof)
        std::cout << "Receive failed" << error.message() << std::endl;
    else{
        const char* data = buffer_cast<const char *>(receive_buffer.data());
        std::cout << "Received: " << data << std::endl;
        if (message == data)
            std::cout << "Messages are equal" << std::endl;
    }
    
    return 0;
}
