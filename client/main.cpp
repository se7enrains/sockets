#include <iostream>
#include "../confighandler/confighandler.h"
#include "client.h"

using std::string;

int main() {
    string path, ip, port;
    std::cout << "Enter path to config: ";
    std::cin >> path;
    std::cin.get();
    ConfigHandler cfg(path);
    ip = cfg.getIp();
    port = cfg.getPort();
    if (cfg.isOk()) {
        Client client(ip, std::stoi(port));
        client.run();
    } else {
        std::cout << cfg.getError() << std::endl;
    }
    
    return 0;
}
