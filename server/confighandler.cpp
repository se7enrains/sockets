//
// Created by se7enrains on 1/30/20.
//

#include "confighandler.h"

bool ConfigHandler::isOk() {
    return ok;
}

string ConfigHandler::getError() {
    return error;
}

ConfigHandler::ConfigHandler(string path) {
    try{
        cfg.readFile(path.c_str());
    }
    catch (const FileIOException &fioex){
        ok = false;
        error = "I/O error while reading file";
    }
    catch (const ParseException &pex){
        ok = false;
        std::stringstream ss;
        ss << "Parse exception at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError();
        error = ss.str();
    }
    ok = true;
    error = "OK";
}

string ConfigHandler::getIp() {
    if (ok) {
        try {
            return cfg.lookup("server.ip").c_str();
        }
        catch (const SettingNotFoundException &snfex) {
            ok = false;
            error = "No \"ip\" value in configuration file";
        }
    }
    return "";
}

string ConfigHandler::getPort() {
    if (ok) {
        try {
            return cfg.lookup("server.port").c_str();
        }
        catch (const SettingNotFoundException &snfex) {
            ok = false;
            error = "No \"port\" value in configuration file";
        }
    }
    return "";
}

void ConfigHandler::closeFile() {

}
