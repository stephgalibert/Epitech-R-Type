#pragma once

#include <functional>

#include "ITask.hpp"

#include "IServerSocket.hpp"
#include "ISocket.hpp"
#include "StaticTools.hpp"

class AcceptAsyncTask : public ITask
{
public:
	AcceptAsyncTask(std::shared_ptr<IServerSocket> ss,
					std::function<void(std::shared_ptr<ISocket>)> callback);
	virtual ~AcceptAsyncTask(void);

	virtual void doInBackground(void);
	virtual void cancel(void);

private:
	std::shared_ptr<IServerSocket> _ss;
	std::function<void(std::shared_ptr<ISocket>)> _callback;
	bool _canceled;
};

