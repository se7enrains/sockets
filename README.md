# sockets
c++ socket echo server made with Boost::asio lib

Enviroment reqirements
-------------------------------------
cmake >= 3.15

boost >= 1.67

libconfig++ >= 1.5

solution was built on Debian with g++ compiler

Running
-------------------------------------
On starting server/client you should specify path to config file

then client connects to server and asks for message to be sent

if everything goes fine, server is sending back the same message
and client compare messages