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

static unsigned char far* VRAM = (unsigned char far*)0xA0000000L;
static unsigned char far* offscreen;

#ifdef __cplusplus
extern "C" {
#endif
void _Cdecl _waitvretrace(void);
void _Cdecl _putpixel(int x, int y, char color);
void _Cdecl _initMode(int mode);

void vgaInit(void);

void vgaExit(void);
  
void vgaPutpixel(int x, int y, char color);

void vgaClroffscreen(char color);

void vgaUpdateVRAM(void);
#ifdef __cplusplus
}
#endif

#endif