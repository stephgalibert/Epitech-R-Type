#pragma once

#include <functional>
#include <memory>

#include "ITask.hpp"
#include "ISocket.hpp"

class ReadAsyncTask : public ITask
{
public:
	ReadAsyncTask(std::shared_ptr<ISocket> socket, size_t transferAtLeast,
		std::function<void(char *, size_t)> callback);
	virtual ~ReadAsyncTask(void);

	virtual void doInBackground(void);
	virtual void cancel(void);

private:
	std::shared_ptr<ISocket> _socket;
	size_t _transferAtLeast;
	std::function<void(char *, size_t)> _callback;
	bool _canceled;
};

