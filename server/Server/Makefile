NAME		=	server

CXX		=	g++

RM		=	rm -f

CXXFLAGS	+=	-Wall -Werror -Wextra
CXXFLAGS	+=	-g -std=c++11

CXXFLAGS	+=	-I./
CXXFLAGS	+=	-I../../common/
CXXFLAGS	+=	-I../../api/

LDFLAGS		+=	-lpthread

SRCS		+=	main.cpp
SRCS		+=	AConnection.cpp
SRCS		+=	Application.cpp
SRCS		+=	AServer.cpp
SRCS		+=	Buffer.cpp
SRCS		+=	ConnectionManager.cpp
SRCS		+=	Party.cpp
SRCS		+=	PartyManager.cpp
SRCS		+=	RequestBuilder.cpp
SRCS		+=	RequestHandler.cpp
SRCS		+=	TCPServer.cpp
SRCS		+=	ThreadPool.cpp
SRCS		+=	UDPServer.cpp
SRCS		+=	UnixServerSocket.cpp
SRCS		+=	UnixSocket.cpp
SRCS		+=	AcceptAsyncTask.cpp
SRCS		+=	ReadAsyncTask.cpp
SRCS		+=	WriteAsyncTask.cpp

SRCS		+=	../../common/StaticTools.cpp

SRCS		+=	../../api/CMDCollision.cpp
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
