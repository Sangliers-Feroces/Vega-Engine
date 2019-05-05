CPPFLAGS = -I./include
CFLAGS = -m64 -Wall -Wextra -fPIC
LDLIB = -lm -lpthread -lcsfml-window -lcsfml-graphics -lcsfml-system -lcsfml-audio

%.o: %.c
	gcc $(CFLAGS) $(CPPFLAGS) -c $< -o $@

SRC = $(filter-out ./src/wrapper/main.c, \
$(wildcard -r ./src/*.c $(wildcard -r ./src/*/*.c) $(wildcard -r ./src/*/*/*.c)))
OBJ = $(SRC:.c=.o)

MAINSRC = $(wildcard ./src/wrapper/main.c)
MAINOBJ = $(MAINSRC:.c=.o)

OUTPUT = my_rpg
LIBXD = libxdworld.so

all: CFLAGS += -O3
all: $(OUTPUT)

$(LIBXD): $(OBJ)
	gcc -shared -Wl,-soname,$(LIBXD) -o $(LIBXD) $(OBJ) $(LDLIB)

$(OUTPUT): $(LIBXD)
	gcc $(CFLAGS) $(CPPFLAGS) $(MAINSRC) $(LIBXD) -Wl,-rpath,. -o $(OUTPUT) $(LDLIB)

clean:
	rm -f $(MAINOBJ) $(OBJ)

fclean: clean
	rm -f $(OUTPUT) $(LIBXD)

re: fclean all

.PHONY: all clean fclean re debug release
