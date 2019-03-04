#include "socket_queue.h"

Socket_queue::Socket_queue() {
}

Socket_queue::~Socket_queue() {
}

void Socket_queue::push(int sockfd) {
	std::unique_lock<std::mutex> lock(mtx_);
	sockets_.push_back(sockfd);
	lock.unlock();
	cond_var_.notify_one();
}

int Socket_queue::pop() {
	std::unique_lock<std::mutex> lock(mtx_);
	while (sockets_.size() == 0) {
		cond_var_.wait(lock);
	}

	auto el = sockets_.front();
	sockets_.pop_front();
	return el;
}