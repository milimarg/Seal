SRC		=	src/main.cpp \
			src/Bus.cpp \
			src/Core.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	seal

CPPFLAGS	=	-Wall -Wextra -std=c++20 -g

all: $(NAME)

$(NAME): $(OBJ)
	g++ $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
