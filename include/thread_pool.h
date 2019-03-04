#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <vector>
#include <thread>

class Thread_pool{
public:
	Thread_pool();
	~Thread_pool();
	Thread_pool(const Thread_pool&) = delete;
	Thread_pool(Thread_pool&&) = delete;
	Thread_pool& operator=(const Thread_pool&) = delete;
	Thread_pool* operator=(Thread_pool&&) = delete;

	void add_consumer(std::thread&& consumer_thread);
	void add_server(std::thread&& server_thread);
	void join_consumers();
	void join_server();

private:
	std::vector<std::thread> consumers_;
	std::vector<std::thread> server_;
};

#endif