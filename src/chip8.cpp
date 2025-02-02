#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <cmath>
#include <bitset>

#include "chip8.h"

void printHex(unsigned int target, unsigned int digits);

unsigned char chip8_fontset[80] = { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() {
    // zero memory
    for (int i = 0; i < 4096; i++) {
        memory[i] = 0;
    }

    for (int i = 0; i < 16; i++) {
        registers[i] = 0;
        input[i] = 0;
    }

    for (int i = 0; i < 32; i++) {
        display[i] = 0;
    }

    // load font set into memory
    for (int i = 0; i < 80; ++i) {
        memory[i] = chip8_fontset[i];
    }

    // intialise values
    pc = 0x200;
    index = 0;
    sp = 0;

    sound = 0;
    delay = 0;

    display[1] = 0x200;
}

int Chip8::load(std::string filename) {
    std::ifstream program(filename, std::ios::binary);

    if (program.is_open()) {
        char * buffer = new char[2048];
        program.read(buffer, 2048);

        for (int i = 0; i < 2048; i++) {
            memory[i + 0x200] = buffer[i];
            // std::cout << std::hex << std::setw(2) << std::setfill('0') << (((unsigned int) memory[i + 0x200]) & 0xff) << ' ';
        }
        
        return 0;
    }

    return -1;
}

int Chip8::cycle() {
    // fetch instruction
    short opcode = memory[pc] << 8 | memory[pc + 1];

    // process opcode
    switch ((opcode >> 12) & 0xf) {
        case 0x0: {
            if (opcode == 0x00e0) {
                // CLS
                for (int i = 0; i < 16; i++) {
                    display[i] = 0;
                }
            } else if (opcode == 0x00ee) {
                // RET
                pc = sp--;
            } 

            break;
        }

        case 0x1: {
            pc = opcode & (4095);
            break;
        }

        case 0x2: {
            stack[sp++] = pc;
            pc = opcode & 4095;
            break;
        }

        case 0x3: {
            unsigned short vx = (opcode >> 8) & 15;
            unsigned short immediate = opcode & (255); 

            if (registers[vx] == immediate) {
                pc += 2;
            }

            break;
        }

        case 0x4: {
            unsigned short vx = (opcode >> 8) & 15;
            unsigned short immediate = opcode & (255); 

            if (registers[vx] != immediate) {
                pc += 2;
            }

            break;
        }

        case 0x5: {
            unsigned short vx = (opcode >> 8) & 15;
            unsigned short vy = (opcode >> 4) & 15;

            if (registers[vx] == registers[vy]) {
                pc += 2;
            }

            break;
        }

        case 0x6: {
            unsigned short vx = (opcode >> 8) & 15;
            unsigned short immediate = opcode & (255);

            registers[vx] = immediate;
            break;
        }

        // TODO check if immediate can be signed
        case 0x7: {
            unsigned short vx = (opcode >> 8) & 15;
            unsigned short immediate = opcode & (255);

            registers[vx] += immediate;
            break;
        }

        case 0x8: {
            unsigned short vx = (opcode >> 8) & 15;
            unsigned short vy = (opcode >> 4) & 15;

            unsigned short operation = opcode & 15;

            switch (operation) {
                case 0x0:
                    registers[vx] = registers[vy];
                    break;

                case 0x1:
                    registers[vx] |= registers[vy];
                    break;

                case 0x2:
                    registers[vx] &= registers[vy];
                    break;

                case 0x3:
                    registers[vx] ^= registers[vy];
                    break;

                // TODO: finish
            }

            break;
        }

        case 0x9: {
            unsigned short vx = (opcode >> 8) & 15;
            unsigned short vy = (opcode >> 4) & 15;

            if (registers[vx] != registers[vy]) {
                pc += 2;
            }

            break;
        }

        case 0xA: {
            unsigned short immediate = opcode & 0xFFF;
            index = immediate;

            break;
        }

        case 0xB: {
            unsigned short immediate = opcode & 4095;
            pc = registers[0] + immediate;

            break;
        }

        case 0xC: {
            unsigned short vx = (opcode >> 8) & 15;
            unsigned short immediate = opcode & 255;

            unsigned short randomNumber = rand() % 256;

            registers[vx] = immediate & randomNumber;
            break;
        }

        case 0xD: {
            unsigned short vx = (opcode >> 8) & 15;
            unsigned short vy = (opcode >> 4) & 15;

            unsigned short n = opcode & 15;

            unsigned short x = registers[vx];
            unsigned short y = registers[vy];

            for (int i = 0; i < n; i++) {
                // read from address at register I
                unsigned long long read = memory[index + i];

                // std::bitset<64>bits(read << (64 - x));
                // std::cout << bits << '\n';

                if (x > 56) {
                    // left part of sprite
                    display[(y + i) % 32] ^= read >> (x - 56);

                    //right part of sprite
                    display[(y + i) % 32] ^= read << (64 - (x - 56));

                } else {
                    display[(y + i) % 32] ^= read << (56 - x);
                }
            }

            // std::cout << std::endl;

            // for (int i = 0; i < 32; i++) {
            //     std::bitset<64>bits(display[i]);
            //     std::cout << bits << '\n';
            // }

            break;
        }
    }

    // modify timers
    if (delay > 0) {
        delay--;
    }

    if (sound > 0) {
        if (sound == 1) {
            std::cout << "sound";
        }

        sound--;
    }

    // print CPU state
    std::cout << "pc: " << pc << " opcode: ";
    std::cout << std::hex << opcode;
    std::cout << " registers: ";

    for (int i = 0; i < 2; i++) {
        std::cout << i << " : ";
        printHex(registers[i], 4);
    }

    std::cout << " index " << index << std::endl;

    // increase program counter on non-jump instructions
    switch (opcode >> 12 & 0xf) {
        case 0x1:
        case 0x2:
        case 0xb:
            break;

        default:
            pc += 2;
    }

    return 0;
}

void printHex(unsigned int target, unsigned int digits) {
    unsigned int mask = std::pow(2, digits * 4) - 1; 
    std::cout << std::hex << std::setw(digits) << std::setfill('0') << (target & mask) <<  " ";
}




