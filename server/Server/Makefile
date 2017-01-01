NAME		=	server

CXX		=	g++

RM		=	rm -f

CXXFLAGS	+=	-Wall -Werror -Wextra
CXXFLAGS	+=	-g -std=c++11

CXXFLAGS	+=	-I./
CXXFLAGS	+=	-I../../common/
CXXFLAGS	+=	-I../../protocol/

LDFLAGS		+=	-lpthread -ldl

SRCS		+=	MonsterManager.cpp
SRCS		+=	ReceiveFromAsyncTask.cpp
SRCS		+=	RequestCollision.cpp
SRCS		+=	RequestScore.cpp
SRCS		+=	RequestMessage.cpp
SRCS		+=	RequestConnect.cpp
SRCS		+=	RequestCreateParty.cpp
SRCS		+=	RequestDestroyed.cpp
SRCS		+=	RequestMove.cpp
SRCS		+=	RequestGameStatus.cpp
SRCS		+=	RequestDisconnect.cpp
SRCS		+=	RequestFire.cpp
SRCS		+=	RequestLoadedPowder.cpp
SRCS		+=	RequestRespawn.cpp
SRCS		+=	RequestGetParty.cpp
SRCS		+=	RequestEffect.cpp
SRCS		+=	SendToAsyncTask.cpp
SRCS		+=	Timer.cpp
SRCS		+=	main.cpp
SRCS		+=	AConnection.cpp
SRCS		+=	TCPConnection.cpp
SRCS		+=	UDPConnection.cpp
SRCS		+=	Application.cpp
SRCS		+=	AServer.cpp
SRCS		+=	Buffer.cpp
SRCS		+=	ConnectionManager.cpp
SRCS		+=	Party.cpp
SRCS		+=	PartyManager.cpp
SRCS		+=	RequestBuilder.cpp
SRCS		+=	RequestHandler.cpp
SRCS		+=	TCPServer.cpp
SRCS		+=	UDPServer.cpp
SRCS		+=	ThreadPool.cpp
SRCS		+=	UnixServerSocket.cpp
SRCS		+=	TCPUnixSocket.cpp
SRCS		+=	AcceptAsyncTask.cpp
SRCS		+=	ReadAsyncTask.cpp
SRCS		+=	WriteAsyncTask.cpp
SRCS		+=	UnixDirectoryParser.cpp
SRCS		+=	ADirectoryParser.cpp
SRCS		+=	LevelManager.cpp
SRCS		+=	LevelParser.cpp
SRCS		+=	PowerupManager.cpp

SRCS		+=	../../common/StaticTools.cpp
SRCS		+=	../../common/Generator.cpp

SRCS		+=	../../protocol/CMDPowder.cpp
SRCS		+=	../../protocol/CMDSpawnPlayer.cpp
SRCS		+=	../../protocol/CMDScore.cpp
SRCS		+=	../../protocol/CMDGetParty.cpp
SRCS		+=	../../protocol/CMDRespawn.cpp
SRCS		+=	../../protocol/CMDGameStatus.cpp
SRCS		+=	../../protocol/CMDCollision.cpp
SRCS		+=	../../protocol/CMDDestroyed.cpp
SRCS		+=	../../protocol/CMDConnect.cpp
SRCS		+=	../../protocol/CMDCreateParty.cpp
SRCS		+=	../../protocol/CMDDisconnected.cpp
SRCS		+=	../../protocol/CMDDisconnect.cpp
SRCS		+=	../../protocol/CMDError.cpp
SRCS		+=	../../protocol/CMDFire.cpp
SRCS		+=	../../protocol/CMDMove.cpp
SRCS		+=	../../protocol/CMDPing.cpp
SRCS		+=	../../protocol/CMDMessage.cpp
SRCS		+=	../../protocol/CMDSpawnPowerUp.cpp
SRCS		+=	../../protocol/CMDSpawnMonster.cpp
SRCS		+=	../../protocol/CMDEffect.cpp
SRCS		+=	../../protocol/CommandFactory.cpp

OBJS		=	$(SRCS:.cpp=.o)


all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
		make -C ../../monsters/Zorg/
		make -C ../../monsters/Ravid/
		make -C ../../monsters/Dop/
		make -C ../../monsters/Gomander/

re:		fclean all

clean:
		$(RM) $(OBJS)
		make clean -C ../../monsters/Zorg/
		make clean -C ../../monsters/Ravid/
		make clean -C ../../monsters/Dop/
		make clean -C ../../monsters/Gomander/

fclean: 	clean
		$(RM) $(NAME)
		make fclean -C ../../monsters/Zorg/
		make fclean -C ../../monsters/Ravid/
		make fclean -C ../../monsters/Dop/
		make fclean -C ../../monsters/Gomander/
