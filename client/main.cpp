#include <iostream>
#include <boost/asio.hpp>
#include <libconfig.h++>

using namespace libconfig;
using namespace boost::asio;
using ip::tcp;
using std::string;


int main() {
    boost::asio::io_service ioService;
    tcp::socket socket(ioService);
    Config cfg;
    try{
        cfg.readFile("./client.cfg");
    }
    catch (const FileIOException &fioex){
        std::cerr << "I/O error while reading file" << std::endl;
        return EXIT_FAILURE;
    }
    catch (const ParseException &pex){
        std::cerr << "Parse exception at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return EXIT_FAILURE;
    }
    string ip, port;
    try{
        ip.assign(cfg.lookup("server.ip").c_str());
        port.assign(cfg.lookup("server.port").c_str());
    }
    catch(const SettingNotFoundException &snfex){
        std::cerr << "No \"ip\" or \"port\" value in configuration file" << std::endl;
        return EXIT_FAILURE;
    }
    socket.connect(tcp::endpoint(
            ip::address::from_string(ip), std::stoi(port)));
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
