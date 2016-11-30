#include "ThreadPool.hpp"

ThreadPool ThreadPool::Pool(16);

void ThreadPool::addTask(ITask *task)
{
	_mtx.lock();
	_vtask.push_back(task);
	_mtx.unlock();
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
	(void)i;
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
		if (task != NULL) {
			task->doInBackground();
			delete (task);
		}
	}
	std::cout << "End" << std::endl;
}
