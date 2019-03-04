#include <iostream>
#include <csignal>

#include "tcp_server.h"

constexpr const unsigned short MSG_LENGTH = 5000;
constexpr const unsigned short PORT = 9100;
constexpr const char* IP = "0.0.0.0";
constexpr const unsigned short MAX_CONNECTIONS = 20;

int main(){
	auto& server = Tcp_server::get_instance();
	server.set_ip_address( IP );
	server.set_port( PORT );
	server.set_timeout_seconds( 5 );
	server.set_message_length( MSG_LENGTH );
	server.set_max_connections( MAX_CONNECTIONS );
	server.set_number_of_consumers(3);
	
	signal(SIGINT, &Tcp_server::stop_server);

	try{
		server.initialize();
	}
	catch(Init_server_error& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	
	server.start_server([&server](int client_socket){
		try{
			auto recv_msg = server.recv_data_from_client(client_socket);
			std::cout << client_socket << ": Message from client: " << recv_msg << std::endl;
			
			server.send_data_to_client(client_socket, "Data has been successfully recieved");
		}
		catch(Timeout_error& e){
			std::cerr << client_socket << ": " << e.what() << std::endl;
		}
		catch(Client_disconnected_error& e){
			std::cerr << client_socket << ": " << e.what() << std::endl;
		}
		catch(Send_error& e){
			std::cerr << client_socket << ": " << e.what() << std::endl;
		}
	});
	server.join_threads();

	std::cout << "\nExit" << std::endl;
	return 0;
}
