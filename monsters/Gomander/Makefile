CXX		=	g++
RM		=	rm -f

CXXFLAGS	+=	-std=c++11 -fPIC
CXXFLAGS	+=	-Wextra -Wall -Werror
CXXFLAGS	+=	-I ../../protocol/
CXXFLAGS	+=	-I ../../common/
CXXFLAGS	+=	-I ../../LuaLib/LuaLib/

LDFLAGS		+=	-L../../LuaLib/LuaLib/ -llua

NAME		=	../../server/Server/monsters/Gomander.so

SRCS		+=	Gomander.cpp
SRCS		+=	StaticTools.cpp
SRCS		+=	../../common/LuaHandler.cpp
SRCS		+=	../../common/lua_adapter.cpp

OBJS		=	$(SRCS:.cpp=.o)

all:		lua $(NAME)

lua:
		make linux -C ../../LuaLib/LuaLib

$(NAME):	$(OBJS)
		$(CXX) -shared $(OBJS) -o $(NAME) $(LDFLAGS)

re: 		fclean all

clean:
		$(RM) $(OBJS)
		make clean -C ../../LuaLib/LuaLib

fclean: 	clean
		$(RM) $(NAME)
