SRC		=	tests/test.cpp \
			src/Bus.cpp \
			src/Core.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	seal

CPPFLAGS	=	-Wall -Wextra -std=c++20 -g -Wno-unknown-pragmas

SFML_FLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

$(NAME): $(OBJ)
	g++ $(OBJ) -o $(NAME) -lGL -lGLU -lglut -lX11 -lpng

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
