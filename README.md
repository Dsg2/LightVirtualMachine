# LightVirtualMachine
Runtime environment for a lightweight virtual machine

## Virtual machine specs:
Interprets a language with syntax inspired by mindustry/assembly, aiming for a minimalstic but powerful language. The runtime is optimised with switch cases, and no runtime error checking for maximimum efficiency.

 - 240x135 screen default
 - 64 default data cells (data cells accessed as c<index>), changing length of memory planned
 - 16 default jmp label table, changing length of jmp table planned
 - currently framebuffer not exposed directly, includes high level vga-inspired text display mode (char is 3x5 + 1 space, padding gives 236x131 usable space, 56 column and 21 row), planned for raw pixel manipulation

## Language documentation:
Keywords:
```
lab <cell|num> - creates a label with value at cell or num

mov <dest> <source> - copies source (cell or num) to dest, dest must be cell

add/sub/mul/div <cell> <cell|num> - does arithmetic, stores output to first cell (must be cell)

jmp <lab> <cond>- jumps to label (cell or num) if cond cell is not 0

vga <ind> <char ind> - writes to screen location ind with value char ind (char ind is line index of vga.dat)

key <char ind> <cell> - gets key is down at char ind (cell or num, based off vga.dat line index), stored to out cell

slp <cell|num> - sleeps for time in seconds

hlt - halts (ends the runtime)
```

**Important:** Note that `hlt` is needed for the VM to automatically stop after code has finished execution, otherwise it will loop back to the first line.

## Example:
countdown.k:
```
mov c0 10
mov c2 0
lab 0
mov c1 c0
add c1 1
vga c2 c1
sub c0 1
add c2 1
slp 1
jmp 0 c0
hlt
```
output:

<img width="475" height="292" alt="image" src="https://github.com/user-attachments/assets/775da615-07a2-4576-a2c2-ca2389b48f5b" />

*Above screenshot shows as numbers 0 - 1 are listed in vga before execution halts*
