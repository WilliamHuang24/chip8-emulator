chip8: chip8.o main.o window.o
	g++ -o chip8 chip8.o main.o window.o -L/src -lSDL2

main.o: src/main.cpp
	g++ -g -c -I/src src/main.cpp

chip8.o: src/chip8.cpp src/chip8.h
	g++ -g -c -I/src src/chip8.cpp

window.o: src/window.cpp src/window.h
	g++ -g -c -I/src src/window.cpp

clean:
	rm -f chip8 chip8.o main.o


