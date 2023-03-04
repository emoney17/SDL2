CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -pedantic -ggdb
LIBS = -lSDL2 -lSDL2_image
SRC = ./main.cpp ./render_window.cpp ./entity.cpp
all:
	$(CC) $(CFLAGS) -o game $(SRC) $(LIBS)
