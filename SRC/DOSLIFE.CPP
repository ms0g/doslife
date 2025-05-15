#include "LIFESIM.H"
#include "RENDERER.H"
#include "KEYBRD.H"
#include "VGA.H"

static int isRunning;
static LifeSimulator lifesim;

void processInput(void) {
    char key = kbhit();

    if (key == ESC) {
        isRunning = 0;
    }
}

void update(void) {
    lifesim.update();
}

void render(void) {
    clear(BLACK);

    lifesim.draw();

    updateBuffer();
}
 
void main(void) {
    isRunning = 1;

    vgaInit();
    initkb();

    while (isRunning) {
        processInput();
        update();
        render();
    }

    vgaExit();
    exitkb();
}


