# Asynchronous TCP/IP server
Simple asynchronous TCP/IP server in Linux

Tcp_server is a singleton class, which provides asynchronous communication with clients. It's based on producent/consumer design pattern. One thread "produces" sockets descriptors, and puts them into thread safe queue. Then other threads "consume" them and exchange data with clients.

To compile example program, you will need cmake and C++ compiler which supports C++11 standard.

In order to run example:
 - go to build directory and type: `cmake ../example/`
 - after configuration is done, hit: `make`
 - executable will appear in `bin/` directory
