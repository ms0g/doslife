#ifndef RENDERER_H
#define RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif
void rnd_rectangle(int x, int y, int width, int height, char color);

void rnd_clear(char color);

void rnd_update_buffer(void);
#ifdef __cplusplus
}
#endif

#endif