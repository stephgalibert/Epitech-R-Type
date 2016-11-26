#pragma once

#include <functional>

#include "ITask.hpp"

#include "IServerSocket.hpp"
#include "ISocket.hpp"
#include "StaticTools.hpp"

class AcceptAsyncTask : public ITask
{
public:
	AcceptAsyncTask(IServerSocket *ss, std::function<void(ISocket *)> function);
	virtual ~AcceptAsyncTask(void);

	virtual void doInBackground(void);

private:
	IServerSocket *_ss;
	std::function<void(ISocket *)> _callback;
};

