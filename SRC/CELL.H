#ifndef CELL_H
#define CELL_H

#define CELL_WIDTH  8
#define CELL_HEIGHT 8
#define CELL_COLOR  0x02

typedef struct {
    int x, y;
    char color;
    int width, height;
    int aliveNeighbors;
} Cell;

#ifdef __cplusplus
extern "C" {
#endif

void cellInit(Cell* cell, int x, int y, int width, int height, char color);

int checkEquality(const Cell* cell1, const Cell* cell2);

#ifdef __cplusplus
}
#endif

#endif