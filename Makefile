CC=g++
CFLAGS= -Wall -Wextra -pedantic
LIBS= -lSDL2
SRC= ./main.cpp ./pong.cpp ./paddle.cpp

all:
	$(CC) $(SRC) -o main $(CFLAGS) $(LIBS)
