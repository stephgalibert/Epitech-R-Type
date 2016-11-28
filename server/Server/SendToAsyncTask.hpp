#pragma once

#include <memory>
#include <functional>

#include "ITask.hpp"
#include "IUDPSocket.hpp"
#include "Endpoint.hpp"

class SendToAsyncTask : public ITask
{
public:
	SendToAsyncTask(std::shared_ptr<IUDPSocket> socket, Endpoint const &endpoint,
		char *buffer, size_t size, std::function<void(void)> callback);
	virtual ~SendToAsyncTask(void);

	virtual void doInBackground(void);
	virtual void cancel(void);

private:
	std::shared_ptr<IUDPSocket> _socket;
	Endpoint _endpoint;
	char *_buffer;
	size_t _size;
	std::function<void(void)> _callback;
	bool _canceled;
};

