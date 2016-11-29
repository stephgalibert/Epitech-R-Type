#pragma once

#include <memory>
#include <functional>

#include "ITask.hpp"
#include "IUDPSocket.hpp"
#include "Endpoint.hpp"

class ReceiveFromAsyncTask : public ITask
{
public:
	ReceiveFromAsyncTask(std::shared_ptr<IUDPSocket> socket, Buffer &buffer,
							Endpoint &endpoint, std::function<void(bool)> callback);
	virtual ~ReceiveFromAsyncTask(void);

	virtual void doInBackground(void);
	virtual void cancel(void);

private:
	std::shared_ptr<IUDPSocket> _socket;
	Buffer &_buffer;
	Endpoint &_endpoint;
	std::function<void(bool)> _callback;
	bool _canceled;
};

