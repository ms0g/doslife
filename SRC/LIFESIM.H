
#ifndef GOL_H
#define GOL_H

#include "VECTOR.H"

#define CELL_WIDTH  8
#define CELL_HEIGHT 8
#define CELL_COLOR  0x02

class Cell {
public:
    Cell() {
        mAliveNeighbors = 0;
    }
    
    Cell(int x, int y, int width = CELL_WIDTH, int height = CELL_HEIGHT, char color = CELL_COLOR): 
        mX(x), mY(y), mWidth(width), mHeight(height), mColor(color) {
        mAliveNeighbors = 0;
    }

    int x(void) const { return mX; }
    int y(void) const { return mY; }
    int width(void) const { return mWidth; }
    int height(void) const { return mHeight; }
    char color(void) const { return mColor; }
   
    int getAliveNeighbors(void) {
        return mAliveNeighbors;
    }

    void resetAliveNeighbors(void) {
        mAliveNeighbors = 0;
    }

    void incrementAliveNeighbors(void) {
        mAliveNeighbors++;
    }

    int operator==(const Cell& other){ 
        return (mX == other.x() && mY == other.y());
    }
    
    int operator!=(const Cell& other){ 
        return !(*this == other);
    }

private:
    char mColor;
    int mX, mY, mWidth, mHeight;
    int mAliveNeighbors;
};

class Renderer;
class LifeSimulator {
public:
    LifeSimulator();

    void update(void);

    void draw(Renderer* renderer);

private:
    void findAliveNeighbors(Cell& cell);

    void checkNeighbor(Cell& currentAlive, Cell& neigh);
    
    vector<Cell> mAliveCells;
    vector<Cell> mNeighboringDeadCells;
    vector<Cell> mNewlyDeadCells;
};

#endif