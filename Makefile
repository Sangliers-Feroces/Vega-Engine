CPPFLAGS = -I.
CFLAGS = -m64 -Wall -Wextra -g
LDLIB = -lm

%.o: %.c
	gcc $(CFLAGS) $(CPPFLAGS) -c $< -o $@

define compile_test
	gcc $(CFLAGS) $(CPPFLAGS) -I./criterion $1 -c -o $1.o
endef

SRC = $(filter-out ./main.c, $(wildcard ./*.c))
OBJ = $(SRC:.c=.o)

MAINSRC = $(wildcard ./main.c)
MAINOBJ = $(MAINSRC:.c=.o)

TESTSRC = $(wildcard ./criterion/*.c)

OUTPUT = my_world

all: $(OUTPUT) #tests_run

$(OUTPUT): $(OBJ) $(MAINOBJ)
	gcc $(CFLAGS) $(CPPFLAGS) $(OBJ) $(MAINOBJ) $(LDLIB) -o $(OUTPUT)

criterion:
	#$(call compile_test, ./criterion/ls_dir_rec_wow.c)
	gcc $(CFLAGS) --coverage $(CPPFLAGS) $(SRC) ./criterion/*.o -D_REDEF \
	-DERR_EXIT=0 $(LDLIB) -lcriterion -o a.out

clean:
	rm -f $(MAINOBJ) $(OBJ)

fclean: clean
	rm -f $(OUTPUT)

re: fclean all

tests_run: criterion
	./a.out -j1
	rm *.o

.PHONY: all clean fclean re criterion tests_run
