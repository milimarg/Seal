SRC		=	tests/test.cpp \
			src/Bus.cpp \
			src/Cpu.cpp \
			src/Ppu.cpp \
			src/Cartridge.cpp \
			src/Mapper/Mapper.cpp \
			src/Mapper/Mapper_000.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	seal

CPPFLAGS	=	-std=c++20 -g

SFML_FLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

# $(SFML_FLAGS)

$(NAME): $(OBJ)
	g++ $(OBJ) -o $(NAME) -lGL -lGLU -lglut -lX11 -lpng

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
