//
// Application.hpp for  in /home/jordan/workspace/R-type/server
//
// Made by jordan
// Login   <jordan@epitech.net>
//
// Started on  Mon Nov 21 16:11:11 2016 jordan
// Last update Mon Nov 21 16:42:58 2016 jordan
//

#pragma once

#include <vector>

#include "TCPServer.hpp"
#include "PartyManager.hpp"
#include "StaticTools.hpp"

class Application
{
public:
	Application(void);
	~Application(void);

	void init(void);
	void run(void);

private:
	PartyManager _pm;
	std::vector<AServer *> _servers;
};
