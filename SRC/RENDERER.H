#ifndef RENDERER_H
#define RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif
void rectangle(int x, int y, int width, int height, char color);

void clear(char color);

void updateBuffer(void);
#ifdef __cplusplus
}
#endif

#endif