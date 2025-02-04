# CHIP-8 Emulator

## Description

This is a simple emulator for the CHIP-8 virtual machine, a popular platform for running simple video games and applications from the 1970s. This emulator allows you to run games and programs originally designed for CHIP-8 systems. 

## Features

- Emulate the CHIP-8 virtual machine
- Run CHIP-8 programs/ROMs
- Render 64x32 pixel display using SDL
- Handle user input from keyboard (mapped to CHIP-8 keys)
- Basic test programs and games

## Usage

The CHIP-8 machine takes one command line argument as a ROM and runs that program.

### Keyboard Mapping

The CHIP-8 virtual machine uses a 16-key keypad, and the keys on your keyboard are mapped as follows:

| CHIP-8 Keypad | Keyboard Key |
|---------------|--------------|
| 1             | 1            |
| 2             | 2            |
| 3             | 3            |
| 4             | 4            |
| 5             | Q            |
| 6             | W            |
| 7             | E            |
| 8             | R            |
| 9             | A            |
| A             | S            |
| B             | D            |
| C             | F            |
| D             | Z            |
| E             | X            |
| F             | C            |

### Display Settings

The emulator can be configured to render the display either in a terminal/console (ASCII-based) or via graphical libraries (like SDL2, Pygame, or other). To change the rendering settings, modify the configuration options in the `settings.py` or equivalent file.

### CPU Speed

The speed of the CPU emulation can be controlled by adjusting the cycle rate in the emulator's main loop. You can experiment with this to make the emulator run faster or slower based on your preferences.
