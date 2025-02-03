#ifndef CHIP8
#define CHIP8

#include <string>
#include <stdint.h>

class Chip8 {


    unsigned char registers[16];
    unsigned short pc;
    unsigned short index;
    unsigned char sound;
    unsigned char delay;

    unsigned short stack[16];
    unsigned short sp;

    public:
        unsigned char memory[4096];
        unsigned long long display[32];
        uint8_t input[16];

        Chip8();
        int cycle();
        int load(std::string filename);
};

#endif