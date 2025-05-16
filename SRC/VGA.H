#ifndef VGA_H
#define VGA_H

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

#ifdef __cplusplus
extern "C" {
#endif
void vga_init(void);

void vga_exit(void);
  
void vga_putpixel(int x, int y, char color);

void vga_clroffscreen(char color);

void vga_update_vram(void);
#ifdef __cplusplus
}
#endif

#endif