#pragma once

#include <string>
#include <memory>

#include "ConnectionManager.hpp"

class Party : public std::enable_shared_from_this<Party>
{
public:
	Party(void);
	~Party(void);

	void init(std::string name, std::string pwd);
	void connect(std::shared_ptr<AConnection> user);
	void move(char *data);
	void fire(char *data);
	void disconnected(char *data);
	void collision(char *data);
	void loop();

private:
	std::string _name;
	std::string _password;
	ConnectionManager _cm;
	//Timer _timer;
};

