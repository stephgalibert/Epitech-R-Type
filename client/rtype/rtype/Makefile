NAME		=	../Debug/.client
NAME_LAUNCHER	=	../Debug/client

SFML_LIB_REL	=	../../../../../Libraries/SFML/lib
SFML_LIB_GEN	=	~/Libraries/SFML/lib
SFML_INCLUDE	=	../../../../../Libraries/SFML/include

CXX		=	g++-4.9

RM		=	rm -f

CXXFLAGS	+=	-Wall -Werror -Wextra
CXXFLAGS	+=	-g -std=c++11 -g3 -ggdb

CXXFLAGS	+=	-I./
CXXFLAGS	+=	-I../../../common/
CXXFLAGS	+=	-I../../../protocol/
CXXFLAGS	+=	-I$(SFML_INCLUDE)

LDFLAGS		+=	-lpthread
LDFLAGS		+=	-lboost_system -lboost_filesystem -ldl
LDFLAGS		+=	-L$(SFML_LIB_REL)
LDFLAGS		+=	-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

SRCS		+=	main.cpp
SRCS		+=	AActor.cpp
SRCS		+=	AArea.cpp
SRCS		+=	ABlock.cpp
SRCS		+=	ACollidable.cpp
SRCS		+=	AController.cpp
SRCS		+=	ADestroyable.cpp
SRCS		+=	ADrawable.cpp
SRCS		+=	AEntity.cpp
SRCS		+=	AExplosion.cpp
SRCS		+=	AMoveable.cpp
SRCS		+=	ANPC.cpp
SRCS		+=	APC.cpp
SRCS		+=	Application.cpp
SRCS		+=	AProjectile.cpp
SRCS		+=	AShip.cpp
SRCS		+=	AStatic.cpp
SRCS		+=	Background.cpp
SRCS		+=	DisplayArea.cpp
SRCS		+=	Explosion.cpp
SRCS		+=	FPSCounter.cpp
SRCS		+=	GameController.cpp
SRCS		+=	InputHandler.cpp
SRCS		+=	Laser.cpp
SRCS		+=	LoadArea.cpp
SRCS		+=	MainMenuController.cpp
SRCS		+=	MemoryFile.cpp
SRCS		+=	MusicBox.cpp
SRCS		+=	Player.cpp
SRCS		+=	ProjectResource.cpp
SRCS		+=	MainMenuResource.cpp
SRCS		+=	RequestBuilder.cpp
SRCS		+=	RequestHandler.cpp
SRCS		+=	SoundBox.cpp
SRCS		+=	TCPClient.cpp
SRCS		+=	Timer.cpp
SRCS		+=	UDPClient.cpp
SRCS		+=	UnloadArea.cpp
SRCS		+=	World.cpp
SRCS		+=	XMLReader.cpp
SRCS		+=	RequestDisconnected.cpp
SRCS		+=	RequestMove.cpp
SRCS		+=	Mate.cpp
SRCS		+=	MenuButton.cpp
SRCS		+=	LoadingController.cpp
SRCS		+=	GameOverController.cpp
SRCS		+=	ConnectionLostController.cpp
SRCS		+=	HUDController.cpp
SRCS		+=	Powdered.cpp
SRCS		+=	LoadedPowdered.cpp
SRCS		+=	RequestGameStatus.cpp
SRCS		+=	RequestGetParty.cpp
SRCS		+=	RequestDestroyed.cpp
SRCS		+=	RequestCollision.cpp
SRCS		+=	RequestFire.cpp
SRCS		+=	RequestRespawn.cpp
SRCS		+=	RequestPowder.cpp
SRCS		+=	LoadedShotLayout.cpp
SRCS		+=	Health.cpp
SRCS		+=	APowerUp.cpp
SRCS		+=	ScoreController.cpp
SRCS		+=	ALayout.cpp
SRCS		+=	RequestMessage.cpp
SRCS		+=	RequestScore.cpp
SRCS		+=	RequestSpawnPowerUp.cpp
SRCS		+=	MessageLayout.cpp
SRCS		+=	MenuServerBrowser.cpp
SRCS		+=	IncreaseNumberOfCanon.cpp
SRCS		+=	EscapeLayout.cpp
SRCS		+=	MenuTextField.cpp
SRCS		+=	QuadTree.cpp
SRCS		+=	RequestSpawnPlayer.cpp
SRCS		+=	MenuTextForm.cpp
SRCS		+=	MenuPopup.cpp
SRCS		+=	MenuConfirmPopup.cpp
SRCS		+=	MenuTextInputPopup.cpp
SRCS		+=	MenuCredits.cpp
SRCS		+=	GameWinController.cpp
SRCS		+=	RequestSpawnMonster.cpp
SRCS		+=	Zork.cpp
SRCS		+=	FireBall.cpp

SRCS		+=	../../../common/StaticTools.cpp
SRCS		+=	../../../common/Generator.cpp

SRCS		+=	../../../protocol/CMDPowder.cpp
SRCS		+=	../../../protocol/CMDDisconnect.cpp
SRCS		+=	../../../protocol/CMDSpawnPlayer.cpp
SRCS		+=	../../../protocol/CMDScore.cpp
SRCS		+=	../../../protocol/CMDRespawn.cpp
SRCS		+=	../../../protocol/CMDGetParty.cpp
SRCS		+=	../../../protocol/CMDGameStatus.cpp
SRCS		+=	../../../protocol/CMDDestroyed.cpp
SRCS		+=	../../../protocol/CMDCollision.cpp
SRCS		+=	../../../protocol/CMDConnect.cpp
SRCS		+=	../../../protocol/CMDCreateParty.cpp
SRCS		+=	../../../protocol/CMDDisconnected.cpp
SRCS		+=	../../../protocol/CMDError.cpp
SRCS		+=	../../../protocol/CMDFire.cpp
SRCS		+=	../../../protocol/CMDMove.cpp
SRCS		+=	../../../protocol/CMDPing.cpp
SRCS		+=	../../../protocol/CMDSpawnMonster.cpp
SRCS		+=	../../../protocol/CMDMessage.cpp
SRCS		+=	../../../protocol/CMDSpawnPowerUp.cpp
SRCS		+=	../../../protocol/CommandFactory.cpp

OBJS		=	$(SRCS:.cpp=.o)


all:		$(NAME) RUN

$(NAME):	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

RUN:
		@echo "export LD_LIBRARY_PATH="$(SFML_LIB_GEN) " && ./.client" > $(NAME_LAUNCHER)
		@chmod 777 $(NAME_LAUNCHER)

re:		fclean all

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)
		$(RM) $(NAME_LAUNCHER)
