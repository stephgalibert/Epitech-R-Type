#pragma once

#include <functional>
#include <memory>

#include "ITask.hpp"
#include "ITCPSocket.hpp"

class ReadAsyncTask : public ITask
{
public:
	ReadAsyncTask(std::shared_ptr<ITCPSocket> socket, Buffer &buffer,
		size_t transferAtLeast, std::function<void(bool)> callback);
	virtual ~ReadAsyncTask(void);

	virtual void doInBackground(void);
	virtual void cancel(void);

private:
	std::shared_ptr<ITCPSocket> _socket;
	Buffer &_buffer;
	size_t _transferAtLeast;
	std::function<void(bool)> _callback;
	bool _canceled;
};

