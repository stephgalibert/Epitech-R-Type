#include "RequestBuilder.hpp"

RequestBuilder::RequestBuilder(void)
{
	//_cmds[PacketType::PT_Kill] = std::bind(&RequestBuilder::kill, this);
}

RequestBuilder::~RequestBuilder(void)
{
}

/*std::unique_ptr<IRequest> RequestBuilder::create(PacketType type) const
{
  if (_cmds.find(type) != _cmds.cend()) {
    return (std::move(_cmds.at(type)()));
  }
  return (NULL);
}

std::unique_ptr<IRequest> RequestBuilder::kill(void) const
{
  return (std::unique_ptr<IRequest>(new Kill));
}*/