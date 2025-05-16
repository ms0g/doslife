#ifndef VGA_H
#define VGA_H

#include <_defs.h>

enum COLORS {
    BLACK,		    /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,		/* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

static unsigned char far* VRAM;
static unsigned char far* offscreen;

#ifdef __cplusplus
extern "C" {
#endif
void _Cdecl _waitvretrace(void);
void _Cdecl _putpixel(int x, int y, char color);
void _Cdecl _initMode(int mode);

void vga_init(void);

void vga_exit(void);
  
void vga_putpixel(int x, int y, char color);

void vga_clroffscreen(char color);

void vga_update_vram(void);
#ifdef __cplusplus
}
#endif

#endif