#pragma once

#include <memory>
#include <functional>

#include "ITask.hpp"
#include "ISocket.hpp"
#include "Buffer.hpp"

class WriteAsyncTask : public ITask
{
public:
	WriteAsyncTask(std::shared_ptr<ISocket> socket, char *buffer, size_t size,
				   std::function<void(void)> callback);
	virtual ~WriteAsyncTask(void);

	virtual void doInBackground(void);
	virtual void cancel(void);

private:
	std::shared_ptr<ISocket> _socket;
	char *_buffer;
	size_t _size;
	std::function<void(void)> _callback;
	bool _canceled;
};