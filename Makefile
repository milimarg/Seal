SRC		=	src/main.cpp \
			src/Bus.cpp \
			src/Cpu.cpp \
			src/Ppu.cpp \
			src/Cartridge.cpp \
			src/Mapper/Mapper.cpp \
			src/Mapper/Mapper_000.cpp \
			src/Emulator.cpp \
			src/Byte.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	seal

CPPFLAGS	=	-std=c++20 -g $(SFML_FLAGS)

SFML_FLAGS	=	-lsfml-system -lsfml-window -lsfml-graphics

all: $(NAME)

$(NAME): $(OBJ)
	g++ $(OBJ) -o $(NAME) $(SFML_FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# run "export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH" if SFML .so files not found