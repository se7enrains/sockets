#include <iostream>
#include "server.h"
#include "../confighandler/confighandler.h"

using std::string;


int main() {
    string path, ip, port;
    std::cout << "Enter path to config: ";
    std::cin >> path;
    ConfigHandler cfg(path);
    ip = cfg.getIp();
    port = cfg.getPort();
    if (cfg.isOk()) {
        Server server(ip, std::stoi(port));
        server.run();
    } else {
        std::cout << cfg.getError() << std::endl;
    }
    return 0;
}
