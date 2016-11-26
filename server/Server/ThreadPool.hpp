#pragma once

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>

typedef void (*Task)();

class ThreadPool 
{
public:
	static ThreadPool Pool;
public:
	ThreadPool(int nb_thread);
	~ThreadPool(void);

	void QueueTask(Task t);

private:
	void start_func(int i);
	Task getTask(void);

	std::condition_variable _condvar;
	std::vector<std::thread> _vth;
	std::mutex _mtx;
	std::vector<Task> _vtask;
	bool _running;
};

