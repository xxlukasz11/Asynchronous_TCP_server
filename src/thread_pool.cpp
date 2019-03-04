#include "thread_pool.h"

#include <utility>

Thread_pool::Thread_pool(){}

Thread_pool::~Thread_pool(){
	join_server();
	join_consumers();
}

void Thread_pool::add_consumer(std::thread&& consumer_thread){
	consumers_.push_back( std::move(consumer_thread) );
}

void Thread_pool::add_server(std::thread&& server_thread){
	server_.push_back( std::move(server_thread) );
}

void Thread_pool::join_consumers(){
	for(auto& t : consumers_){
		if(t.joinable())
			t.join();
	}
}

void Thread_pool::join_server(){
	for(auto& t : server_){
		if(t.joinable())
			t.join();
	}
}

