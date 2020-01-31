//
// Created by se7enrains on 1/30/20.
//

#ifndef SERVER_CONFIGHANDLER_H
#define SERVER_CONFIGHANDLER_H

#include <libconfig.h++>
#include <sstream>

using namespace libconfig;
using std::string;

class ConfigHandler {
private:
    Config cfg;
    bool ok;
    string error;
public:
    bool isOk();
    string getError();
    explicit ConfigHandler(const string& path);
    string getIp();
    string getPort();
};


#endif //SERVER_CONFIGHANDLER_H