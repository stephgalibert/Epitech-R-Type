#include "RequestGameStatus.hpp"
#include "GameController.hpp"

RequestGameStatus::RequestGameStatus(void)
{
}

RequestGameStatus::~RequestGameStatus(void)
{
}

void RequestGameStatus::execute(IClient &client, std::shared_ptr<ICommand> data,
								std::shared_ptr<ICommand> &toSend)
{
	(void)toSend;
	GameStatus const *gameStatus = reinterpret_cast<GameStatus const *>(data->getData());
	GameStatusType status = gameStatus->status;

	GameController *game = client.getGameController();
	if (game) {
		game->setGameStatus(status);
	}
}