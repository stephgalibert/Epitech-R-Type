NAME		=	../Debug/.client
NAME_LAUNCHER	=	../Debug/client

SFML_LIB_REL	=	../../../../../Libraries/SFML/lib
SFML_LIB_GEN	=	~/Libraries/SFML/lib
SFML_INCLUDE	=	../../../../../Libraries/SFML/include

CXX		=	g++

RM		=	rm -f

CXXFLAGS	+=	-Wall -Werror -Wextra
CXXFLAGS	+=	-g -std=c++11

CXXFLAGS	+=	-I./
CXXFLAGS	+=	-I../../../common/
CXXFLAGS	+=	-I../../../api/
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
SRCS		+=	Generator.cpp
SRCS		+=	InputHandler.cpp
SRCS		+=	Laser.cpp
SRCS		+=	LevelResource.cpp
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
SRCS		+=	RequestSpawn.cpp
SRCS		+=	RequestDisconnect.cpp
SRCS		+=	RequestMove.cpp
SRCS		+=	Mate.cpp
SRCS		+=	MenuButton.cpp

SRCS		+=	../../../common/StaticTools.cpp

SRCS		+=	../../../api/CMDDestroyed.cpp
SRCS		+=	../../../api/CMDCollision.cpp
SRCS		+=	../../../api/CMDConnect.cpp
SRCS		+=	../../../api/CMDCreateParty.cpp
SRCS		+=	../../../api/CMDDisconnected.cpp
SRCS		+=	../../../api/CMDError.cpp
SRCS		+=	../../../api/CMDFire.cpp
SRCS		+=	../../../api/CMDMove.cpp
SRCS		+=	../../../api/CMDPing.cpp
SRCS		+=	../../../api/CMDSpawn.cpp
SRCS		+=	../../../api/CommandFactory.cpp

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
