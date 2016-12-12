NAME		=	server

CXX		=	g++

RM		=	rm -f

CXXFLAGS	+=	-Wall -Werror -Wextra
CXXFLAGS	+=	-g -std=c++11

CXXFLAGS	+=	-I./
CXXFLAGS	+=	-I../../common/
CXXFLAGS	+=	-I../../api/

LDFLAGS		+=	-lpthread

SRCS		+=	MonsterManager.cpp
SRCS		+=	ReceiveFromAsyncTask.cpp
SRCS		+=	RequestCollision.cpp
SRCS		+=	RequestConnect.cpp
SRCS		+=	RequestCreateParty.cpp
SRCS		+=	RequestDestroyed.cpp
SRCS		+=	RequestMove.cpp
SRCS		+=	RequestGameStatus.cpp
SRCS		+=	RequestFire.cpp
SRCS		+=	RequestLoadedPowder.cpp
SRCS		+=	RequestRespawn.cpp
SRCS		+=	RequestGetParty.cpp
SRCS		+=	ScheduledMonster.cpp
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

SRCS		+=	../../common/StaticTools.cpp

SRCS		+=	../../api/CMDPowder.cpp
SRCS		+=	../../api/CMDScore.cpp
SRCS		+=	../../api/CMDGetParty.cpp
SRCS		+=	../../api/CMDRespawn.cpp
SRCS		+=	../../api/CMDGameStatus.cpp
SRCS		+=	../../api/CMDCollision.cpp
SRCS		+=	../../api/CMDDestroyed.cpp
SRCS		+=	../../api/CMDConnect.cpp
SRCS		+=	../../api/CMDCreateParty.cpp
SRCS		+=	../../api/CMDDisconnected.cpp
SRCS		+=	../../api/CMDError.cpp
SRCS		+=	../../api/CMDFire.cpp
SRCS		+=	../../api/CMDMove.cpp
SRCS		+=	../../api/CMDPing.cpp
SRCS		+=	../../api/CMDSpawn.cpp
SRCS		+=	../../api/CommandFactory.cpp

OBJS		=	$(SRCS:.cpp=.o)


all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

re:		fclean all

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)
