CPPFLAGS = -I./include
CFLAGS = -m64 -Wall -Wextra -fPIC
LDLIB = -lm -lpthread -lcsfml-window -lcsfml-graphics

%.o: %.c
	gcc $(CFLAGS) $(CPPFLAGS) -c $< -o $@

SRC = $(filter-out ./src/main.c, $(wildcard ./src/*.c))
OBJ = $(SRC:.c=.o)

MAINSRC = $(wildcard ./src/main.c)
MAINOBJ = $(MAINSRC:.c=.o)

OUTPUT = my_world
LIBXD = libxdworld.so

debug: CFLAGS += -g
debug: all

release: CFLAGS += -O3
release: all

all: $(OUTPUT)

$(LIBXD): $(OBJ)
	gcc -shared $(LDLIB) -Wl,-soname,$(LIBXD) -o $(LIBXD) $(OBJ)

$(OUTPUT): $(LIBXD)
	gcc $(CFLAGS) $(CPPFLAGS) $(MAINSRC) ./$(LIBXD) -o $(OUTPUT)

clean:
	rm -f $(MAINOBJ) $(OBJ)

fclean: clean
	rm -f $(OUTPUT) $(LIBXD)

re: fclean all

.PHONY: all clean fclean re debug release
