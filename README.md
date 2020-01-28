# sockets
c++ socket echo server made with Boost::asio lib

Enviroment reqirements
-------------------------------------
cmake >= 3.15
boost >= 1.67
libconfig++ >= 1.5

solution was built on Debian with g++ compiler

to launch server/client you should put .cfg file in same folder
after launching server it starts waiting for client
when client's message echoed, server asks if it should continue listen or not
