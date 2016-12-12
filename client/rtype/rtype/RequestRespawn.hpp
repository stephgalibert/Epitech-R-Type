#include "IRequest.hpp"

class RequestRespawn : public IRequest
{
public:
	RequestRespawn(void);
	virtual ~RequestRespawn(void);

	virtual void execute(IClient &client, std::shared_ptr<ICommand> data,
						 std::shared_ptr<ICommand> &toSend);
};
