#include <iostream>
#include <boost/asio.hpp>
#include <libconfig.h++>

using namespace libconfig;
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
    std::cout << "Enter absolute path to config: ";
    string configPath;
    std::getline(std::cin, configPath, '\n');
    Config cfg;
    try{
        cfg.readFile(configPath.c_str());
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
    io_service ioService;
    tcp::acceptor acceptor(ioService, tcp::endpoint(ip::address::from_string(ip), std::stoi(port)));
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
