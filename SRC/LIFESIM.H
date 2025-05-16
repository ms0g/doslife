
#ifndef LIFESIM_H
#define LIFESIM_H

#include "VECTOR.H"
#include "CELL.H"

#define CELL_WIDTH  8
#define CELL_HEIGHT 8
#define CELL_COLOR  0x02

class LifeSimulator {
public:
    LifeSimulator();

    void update(void);

    void draw(void);

private:
    void findAliveNeighbors(Cell* cell);

    void checkNeighbor(Cell* currentAlive, Cell* neighbor);
    
    vector<Cell> mAliveCells;
    vector<Cell> mNeighboringDeadCells;
    vector<Cell> mNewlyDeadCells;
};

#endif