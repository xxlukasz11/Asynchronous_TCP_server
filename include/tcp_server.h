#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include <iostream>
#include <string>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/fcntl.h>

#include "tcp_server_exceptions.h"
#include "socket_queue.h"
#include "thread_pool.h"

class Tcp_server {
public:
	~Tcp_server();
	Tcp_server(const Tcp_server&) = delete;
	Tcp_server(Tcp_server&&) = delete;
	Tcp_server& operator=(const Tcp_server&) = delete;
	Tcp_server& operator=(Tcp_server&&) = delete;

	// get instance method
	static Tcp_server& get_instance();

	// setters
	void set_ip_address(std::string ip_address);
	void set_port(int port);
	void set_message_length(int length);
	void set_max_connections(int max_connsctions);
	void set_timeout_seconds(int seconds);
	void set_number_of_consumers(int n_consumers);

	// public methods
	template<typename T>
	void start_server(T handler);
	void initialize();
	void join_threads();
	void send_data_to_client(const int client_socket, std::string msg);
	std::string recv_data_from_client(const int client_socket);
	static void stop_server(int);

private:
	// private constructor
	Tcp_server() = default;
	
	// private methods
	void run_server();
	
	template<typename T>
	void run_consumer(T handler);
	
	void release_consumers();
	
	// Internal constants
	enum Constants {
		DUMMY_SOCKET_ = -123456,
	};

	// configuration
	std::string ip_address_{ "0.0.0.0" };
	int port_ = { 9100 };
	int message_length_{ 1000 };
	int max_connections_{ 50 };
	int timeout_seconds_{ 5 };
	int number_of_consumers_{ 3 };

	// private members
	int server_socket_{ 0 };
	Socket_queue queue_;
	Thread_pool threads_manager_;
	static bool server_is_running_;
};

template<typename T>
void Tcp_server::start_server(T handler){
	Tcp_server::server_is_running_ = true;
	for(int i = 0; i < number_of_consumers_; ++i)
		threads_manager_.add_consumer( std::thread(&Tcp_server::run_consumer<decltype(handler)>, this, handler) );
	
	threads_manager_.add_server( std::thread(&Tcp_server::run_server, this) );
}

template<typename T>
void Tcp_server::run_consumer(T handler){
	while(server_is_running_){
		int client_socket = queue_.pop();
		
		if(client_socket == Tcp_server::DUMMY_SOCKET_)
			break;
		
		if(client_socket < 0) {
			std::cerr << client_socket << ": Error while accepting connection" << std::endl;
			continue;
		}
		
		std::cout << client_socket << ": Connection accepted" << std::endl;

		try{
			struct timeval tv{ Tcp_server::timeout_seconds_, 0 };
			if( setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval*) &tv, sizeof(struct timeval)) < 0){
				throw Sockopt_error("Error while setting timeout opt");
			}

			handler(client_socket);
		}
		catch(Sockopt_error& e){
			std::cerr << client_socket << ": " << e.what() << std::endl;
		}
		
		std::cout << client_socket << ": Connection closed" << std::endl;
		shutdown(client_socket, SHUT_RDWR);
	}
}

#endif
