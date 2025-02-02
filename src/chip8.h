#ifndef CHIP8
#define CHIP8

#include <string>

class Chip8 {
    unsigned char memory[4096];

    unsigned char registers[16];
    unsigned short pc;
    unsigned short index;
    unsigned char sound;
    unsigned char delay;

    unsigned short stack[16];
    unsigned short sp;

    unsigned char key[16];

    public:
        unsigned long long display[32];

        Chip8();
        void cycle();
        int load(std::string filename);
};

#endif