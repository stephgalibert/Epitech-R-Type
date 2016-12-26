CXX		=	g++
RM		=	rm -f

CXXFLAGS	+=	-std=c++11 -fPIC
CXXFLAGS	+=	-Wextra -Wall -Werror
CXXFLAGS	+=	-I ../../protocol/

NAME		=	../../server/Server/monsters/Zorg.so
SRCS		=	Zorg.cpp
OBJS		=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -shared $(OBJS) -o $(NAME) $(LDFLAGS)

re: 		fclean all

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)
