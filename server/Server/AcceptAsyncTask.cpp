#include "AcceptAsyncTask.hpp"

AcceptAsyncTask::AcceptAsyncTask(IServerSocket *ss, std::function<void(ISocket *)> function)
	: _ss(ss),
	  _callback(function)
{
}

AcceptAsyncTask::~AcceptAsyncTask(void)
{
}

#include <iostream>
void AcceptAsyncTask::doInBackground(void)
{
	ISocket *socket = _ss->accept();

	_callback(socket);

	std::cout << "ok" << std::endl;
}