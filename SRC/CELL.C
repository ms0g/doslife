#include "CELL.H"

void cellInit(Cell* cell, int x, int y, int width, int height, char color) {
    cell->x = x;
    cell->y = y;
    cell->width = width;
    cell->height = height;
    cell->color = color;
    cell->aliveNeighbors = 0;
}

int checkEquality(const Cell* cell1, const Cell* cell2) {
    return (cell1->x == cell2->x && cell1->y == cell2->y);
}

