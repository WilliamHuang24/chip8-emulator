chip8: chip8.o main.o
	g++ -g -o chip8 chip8.o main.o -L/src -lSDL2

main.o: src/main.cpp
	g++ -g -c -I/src src/main.cpp

chip8.o: src/chip8.cpp src/chip8.h
	g++ -g -c -I/src src/chip8.cpp




