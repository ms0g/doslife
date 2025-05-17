#include "RENDERER.H"
#include "VGA.H"

void rnd_init(void) {
    vga_init();
}

void rnd_exit(void) {
    vga_exit();
}

void rnd_rectangle(int x, int y, int width, int height, char color) {
    int i,j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            vga_putpixel(x + i, y + j, color);
        }
    }
}

void rnd_clear(char color) {
    vga_clroffscreen(color);
}

void rnd_update_buffer(void) {
    vga_update_vram();
}