CC = gcc
RM = rm -f

CFLAGS = -Wall -g3 -O0
LIBS = -lm -lGL -lGLU -lglut

NAME = cg-geometric-shapes

OBJECTS = main.o sphere.o cylinder.o cone.o toroid.o logging.o texture.o

.SUFFIXES: .c
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJECTS) $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	$(RM) $(OBJECTS) $(NAME)

run:
	./$(NAME)