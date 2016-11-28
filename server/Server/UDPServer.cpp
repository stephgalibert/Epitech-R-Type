#include "UDPServer.hpp"

UDPServer::UDPServer(ConnectionManager &cm, PartyManager &pm)
	: AServer(cm, pm)
{
  //_connection = std::make_shared<AConnection>(cm, getRequestHandler(), pm);
}

UDPServer::~UDPServer(void)
{
}


void UDPServer::init(void)
{

}

void UDPServer::open(void)
{
  //_connection->start();
}

void UDPServer::close(void)
{
	std::clog << "shuting down UDP server ..." << std::endl;
	std::clog << "UDP server shutdown success" << std::endl;
}
