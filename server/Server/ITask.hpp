#pragma once

struct ITask
{
	virtual ~ITask(void) {}
	virtual void doInBackground(void) = 0;
	virtual void cancel(void) = 0;
};