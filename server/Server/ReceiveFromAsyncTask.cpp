#include "ReceiveFromAsyncTask.hpp"

ReceiveFromAsyncTask::ReceiveFromAsyncTask(std::shared_ptr<IUDPSocket> socket, Buffer &buffer,
											Endpoint &endpoint, std::function<void(bool)> callback)
	: _socket(socket),
	  _buffer(buffer),
	  _endpoint(endpoint),
	  _callback(callback)
{
}

ReceiveFromAsyncTask::~ReceiveFromAsyncTask(void)
{
}

void ReceiveFromAsyncTask::doInBackground(void)
{
	_buffer.prepare(2048);
	_socket->recvFrom(_buffer, _endpoint);

	_callback(true);
}

void ReceiveFromAsyncTask::cancel(void)
{
	_canceled = false;
}