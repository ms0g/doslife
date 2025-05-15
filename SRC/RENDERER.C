#include "RENDERER.H"
#include "VGA.H"

void rectangle(int x, int y, int width, int height, char color) {
    int i,j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            vgaPutpixel(x + i, y + j, color);
        }
    }
}

void clear(char color) {
    vgaClroffscreen(color);
}

void updateBuffer(void) {
    vgaUpdateVRAM();
}