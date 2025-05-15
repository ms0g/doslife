#ifndef KEYBOARD_H
#define KEYBOARD_H

#define R_ARROW     0x4D
#define L_ARROW     0x4B
#define ESC         0x01

#ifdef __cplusplus
extern "C" {
#endif
void initkb(void);

void exitkb(void);

unsigned char kbhit(void);
#ifdef __cplusplus
}
#endif

#endif

