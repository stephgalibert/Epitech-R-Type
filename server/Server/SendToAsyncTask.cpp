#include "SendToAsyncTask.hpp"

SendToAsyncTask::SendToAsyncTask(std::shared_ptr<IUDPSocket> socket, Endpoint const &endpoint,
									char *buffer, size_t size, std::function<void(void)> callback)
	: _socket(socket),
	_endpoint(endpoint),
	_buffer(buffer),
	_size(size),
	_callback(callback),
	_canceled(false)
{
}

SendToAsyncTask::~SendToAsyncTask(void)
{
}

void SendToAsyncTask::doInBackground(void)
{
	_socket->sendTo(_buffer, _size, _endpoint);
	_callback();
}

void SendToAsyncTask::cancel(void)
{
	_canceled = true;
}