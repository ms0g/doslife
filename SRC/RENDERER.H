#ifndef RENDERER_H
#define RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif
void rndInit(void);

void rndExit(void);

void rndDrawRectangle(int x, int y, int width, int height, char color);

void rndClear(char color);

void rndUpdateBuffer(void);
#ifdef __cplusplus
}
#endif

#endif