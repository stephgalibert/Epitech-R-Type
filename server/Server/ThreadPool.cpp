#include "ThreadPool.hpp"

ThreadPool ThreadPool::Pool(16);

void ThreadPool::QueueTask(ITask *task)
{
	//std::cout << "before lock" << std::endl; // dead lock here
	_mtx.lock();
	//std::cout << "after lock" << std::endl;
	_vtask.push_back(task);
	//std::cout << "before unlock" << std::endl;
	_mtx.unlock();
	//std::cout << "after unlock" << std::endl;
	_condvar.notify_one();
	
}

ThreadPool::ThreadPool(int nb_thread)
{
	_running = true;
	for (int i = 0; i < nb_thread; i++) {
		_vth.push_back(std::thread([&]() {this->start_func(i); }));
	}
}

ThreadPool::~ThreadPool(void)
{
	_running = false;
	_condvar.notify_all();
	for (size_t i = 0; i < _vth.size(); i++) {
		if (_vth[i].joinable()) {
			_vth[i].join();
		}
	}
}

ITask *ThreadPool::getTask(void)
{
	ITask *task = NULL;

	if (!_vtask.empty()) {
		task = _vtask[0];
		_vtask.erase(_vtask.begin());
	}
	return (task);
}

void ThreadPool::start_func(int i)
{
	while (_running)
	{
		ITask *task = NULL;
		{
			std::unique_lock<std::mutex> lock(_mtx);
			while (_running && _vtask.empty()) {
				_condvar.wait(lock);
			}
			task = getTask();
		}
		//std::cout << "Thread " << i << " : ";
		if (task != NULL) {
			task->doInBackground();
			delete (task);
		}
	}
	std::cout << "End" << std::endl;
}
