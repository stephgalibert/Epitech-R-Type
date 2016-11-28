#pragma once

#include <memory>
#include <functional>

#include "ITask.hpp"
#include "IUDPSocket.hpp"
#include "Endpoint.hpp"

class ReceiveFromAsyncTask : public ITask
{
public:
	ReceiveFromAsyncTask(std::shared_ptr<IUDPSocket> socket, Endpoint &endpoint,
						std::function<void(char *, size_t)> callback);
	virtual ~ReceiveFromAsyncTask(void);

	virtual void doInBackground(void);
	virtual void cancel(void);

private:
	std::shared_ptr<IUDPSocket> _socket;
	Endpoint &_endpoint;
	std::function<void(char *, size_t)> _callback;
	bool _canceled;
};

