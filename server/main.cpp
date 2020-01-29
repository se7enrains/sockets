#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <libconfig.h++>

using namespace libconfig;
using namespace boost::asio;
using ip::tcp;
using std::string;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

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


void client_session(const socket_ptr& socket){
    string message = readSocket(*socket);
    sendSocket(*socket, message);
    socket->close();
}


int main() {
    Config cfg;
    try{
        cfg.readFile("./server.cfg");
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
    tcp::acceptor acceptor(ioService,
                           tcp::endpoint(ip::address::from_string(ip),
                                   std::stoi(port)));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        socket_ptr socket(new ip::tcp::socket(ioService));
        acceptor.accept(*socket);
        boost::thread(boost::bind(client_session, socket));
    }
#pragma clang diagnostic pop
    return 0;
}
