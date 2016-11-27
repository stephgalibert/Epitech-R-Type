#pragma once

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>

#include "ITask.hpp"

//typedef void (*Task)();

class ThreadPool 
{
public:
	static ThreadPool Pool;

public:
	ThreadPool(int nb_thread);
	~ThreadPool(void);

	void addTask(ITask *task);

private:
	void start_func(int i);
	ITask *getTask(void);

	std::condition_variable _condvar;
	std::vector<std::thread> _vth;
	std::mutex _mtx;
	std::vector<ITask *> _vtask;
	bool _running;
};

