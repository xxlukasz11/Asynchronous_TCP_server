# Asynchronous_TCP_server
Simple asynchronous TCP/IP server in Linux

Tcp_server is a singleton class, which provides asynchronous communication with clients. It's based on producent/consumer design pattern. One thread "produces" sockets descriptors, and puts them into thread safe queue. Then other threads "consume" them and exchange data with clients.

You can define your own procedure what to do when connection with client is established:
```c++
server.start_server([&server](int client_socket){
  ...
});
```
