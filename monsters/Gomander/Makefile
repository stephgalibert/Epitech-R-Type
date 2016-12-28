CXX		=	g++
RM		=	rm -f

CXXFLAGS	+=	-std=c++11 -fPIC
CXXFLAGS	+=	-Wextra -Wall -Werror
CXXFLAGS	+=	-I ../../protocol/
CXXFLAGS	+=	-I ../../common/

NAME		=	../../server/Server/monsters/Gomander.so
SRCS		+=	Gomander.cpp
SRCS		+=	StaticTools.cpp
OBJS		=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -shared $(OBJS) -o $(NAME) $(LDFLAGS)

re: 		fclean all

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)
