#pragma once

#include <functional>
#include <memory>

#include "ITask.hpp"
#include "ITCPSocket.hpp"

class ReadAsyncTask : public ITask
{
public:
	ReadAsyncTask(std::shared_ptr<ITCPSocket> socket, size_t transferAtLeast,
		std::function<void(char *, size_t)> callback);
	virtual ~ReadAsyncTask(void);

	virtual void doInBackground(void);
	virtual void cancel(void);

private:
	std::shared_ptr<ITCPSocket> _socket;
	size_t _transferAtLeast;
	std::function<void(char *, size_t)> _callback;
	bool _canceled;
};

