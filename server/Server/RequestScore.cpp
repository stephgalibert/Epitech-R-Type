#include "RequestScore.hpp"

RequestScore::RequestScore(void)
{
}

RequestScore::~RequestScore(void)
{
}

void RequestScore::execute(std::shared_ptr<AConnection> owner,
						   std::shared_ptr<ICommand> received,
						   std::shared_ptr<ICommand> &reply)
{
	(void)owner;
	(void)received;
	(void)reply;
}