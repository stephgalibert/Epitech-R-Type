#include "ReceiveFromAsyncTask.hpp"

ReceiveFromAsyncTask::ReceiveFromAsyncTask(std::shared_ptr<IUDPSocket> socket, Endpoint &endpoint,
										std::function<void(char *, size_t)> callback)
	: _socket(socket),
	  _endpoint(endpoint),
	  _callback(callback)
{
}

ReceiveFromAsyncTask::~ReceiveFromAsyncTask(void)
{
}

void ReceiveFromAsyncTask::doInBackground(void)
{
	Buffer buffer;

	buffer.prepare(2048);
	_socket->recvFrom(buffer, _endpoint);

	_callback(buffer.getData(), buffer.getSize());
}

void ReceiveFromAsyncTask::cancel(void)
{
	_canceled = false;
}