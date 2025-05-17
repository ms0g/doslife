#ifndef CELL_H
#define CELL_H

#define CELL_WIDTH  8
#define CELL_HEIGHT 8
#define CELL_COLOR  0x02

typedef struct {
    int x, y;
    char color;
    int width, height;
    int aliveNeighborsCount;
} Cell;

typedef struct {    
    int count;      
    int capacity;   
    Cell* data;     
} CellArray;   

void cell_init(Cell* cell, int x, int y, int width, int height, char color);
int cell_is_equal(const Cell* c1, const Cell* c2);

void ca_init(CellArray* ca, int size);
void ca_pushback(CellArray* ca, Cell* cell);
void ca_remove(CellArray* ca, int index);
Cell* ca_at(CellArray* ca, int index);
void ca_clear(CellArray* ca);
void ca_free(CellArray* ca);

#endif