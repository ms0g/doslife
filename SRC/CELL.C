#include "CELL.H"
#include <stdlib.h>

void cell_init(Cell* cell, int x, int y, int width, int height, char color) {
    cell->x = x;
    cell->y = y;
    cell->width = width;
    cell->height = height;
    cell->color = color;
    cell->aliveNeighborsCount = 0;
}

int cell_is_equal(const Cell* c1, const Cell* c2) {
    if (c1 == NULL || c2 == NULL) {
        return 0;
    }
    
    return (c1->x == c2->x && c1->y == c2->y);
}

void ca_init(CellArray* ca, int size) {
    ca->count = 0;
    ca->capacity = size;
    ca->data = (Cell*)malloc(size * sizeof(Cell));
}

void ca_pushback(CellArray* ca, Cell* cell) {
    if (ca->count == ca->capacity) {
        ca->capacity *= 2;
        ca->data = (Cell*)realloc(ca->data, ca->capacity * sizeof(Cell));
    }

    ca->data[ca->count++] = *cell;
}

void ca_remove(CellArray* ca, int index) {
    int i;

    if (index < 0 || index >= ca->count) {
        return;
    }
    
    for (i = index; i < ca->count - 1; i++) {
        ca->data[i] = ca->data[i + 1];
    }
    
    ca->count--;
}

Cell* ca_at(CellArray* ca, int index) {
    if (index < 0 || index >= ca->count) {
        return NULL;
    }

    return &ca->data[index];
}

void ca_clear(CellArray* ca) {
    memset(ca->data, 0, ca->count * sizeof(Cell));
    ca->count = 0;
}

void ca_free(CellArray* ca) {
    free(ca->data);
    ca->data = NULL;
}

