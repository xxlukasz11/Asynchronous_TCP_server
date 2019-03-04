#ifndef _SOCKET_QUEUE_H_
#define _SOCKET_QUEUE_H_

#include <mutex>
#include <deque>
#include <condition_variable>

class Socket_queue {
	std::mutex mtx_;
	std::condition_variable cond_var_;
	std::deque<int> sockets_;

public:
	Socket_queue();
	~Socket_queue();
	Socket_queue(const Socket_queue&) = delete;
	Socket_queue(Socket_queue&&) = delete;
	Socket_queue& operator=(const Socket_queue&) = delete;
	Socket_queue& operator=(Socket_queue&&) = delete;

	void push(int sockfd);
	int pop();
};

#endif