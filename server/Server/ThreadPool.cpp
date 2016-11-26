#include "ThreadPool.hpp"

/*void test() {
	std::cout << "LOOOL" << std::endl;
}

int main() {
	ThreadPool Tp(8);

	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	Tp.QueueTask(&test);
	_sleep(500000);
	return 0;
}*/

ThreadPool ThreadPool::Pool(16);

void ThreadPool::QueueTask(Task t)
{
	_mtx.lock();
	_vtask.push_back(t);
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

Task ThreadPool::getTask(void)
{
	Task t = NULL;

	if (!_vtask.empty()) {
		t = _vtask[0];
		_vtask.erase(_vtask.begin());
	}
	return (t);
}

void ThreadPool::start_func(int i)
{
	while (_running)
	{
		std::unique_lock<std::mutex> lock(_mtx);
		while (_running && _vtask.empty())
			_condvar.wait(lock);
		Task t = getTask();
		std::cout << "Thread " << i << " : ";
		if (t != NULL)
			t();
	}
	std::cout << "End" << std::endl;
}
