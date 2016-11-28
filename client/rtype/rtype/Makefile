NAME		=	../Debug/client

CXX		=	g++

RM		=	rm -f

CXXFLAGS	+=	-Wall -Werror -Wextra
CXXFLAGS	+=	-g -std=c++11

CXXFLAGS	+=	-I./
CXXFLAGS	+=	-I../../../common/
CXXFLAGS	+=	-I../../../api/
CXXFLAGS	+=	-I../../../../../Libraries/SFML/include/

LDFLAGS		+=	-lpthread
LDFLAGS		+=	-lboost_system -lboost_filesystem -ldl
LDFLAGS		+=	-L../../../../../Libraries/SFML/lib/
LDFLAGS		+=	-lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-network

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
SRCS		+=	RequestBuilder.cpp
SRCS		+=	RequestHandler.cpp
SRCS		+=	SoundBox.cpp
SRCS		+=	SplashScreen.cpp
SRCS		+=	TCPClient.cpp
SRCS		+=	Timer.cpp
SRCS		+=	UDPClient.cpp
SRCS		+=	UnloadArea.cpp
SRCS		+=	World.cpp
SRCS		+=	XMLReader.cpp

SRCS		+=	../../../common/StaticTools.cpp

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


all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

re:		fclean all

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)
