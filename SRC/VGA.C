#include "VGA.H"
#include <string.h>
#include <malloc.h>
// VGA Graphics Mode
#define MODE_VGA_13H 0x13
// VGA Text Mode
#define MODE_VGA_3H  0x3

#define VRAM_SIZE 64000u

void vga_init(void) {
    VRAM = (unsigned char far*)0xA0000000L;
    offscreen = (unsigned char far*)farmalloc(VRAM_SIZE);

    if (offscreen) {
        _fmemset(offscreen, 0, VRAM_SIZE);
        _initMode(MODE_VGA_13H);
    } 
}

void vga_exit(void) {
     farfree(offscreen);
    _initMode(MODE_VGA_3H);
}

void vga_clroffscreen(char color) {
    _fmemset(offscreen, color, VRAM_SIZE);
}

void vga_putpixel(int x, int y, char color) {
    offscreen[(y << 8) + (y << 6) + x] = color;
}

void vga_update_vram(void) {
    _waitvretrace();
    _fmemcpy(VRAM, offscreen, VRAM_SIZE);
}
