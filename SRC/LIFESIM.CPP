#include "LIFESIM.H"
#include "RENDERER.H"
#include "STATES.H"

LifeSimulator::LifeSimulator() {
    mAliveCells.reserve(INITIAL_CELL_COUNT);
    
    for (int i = 0; i < INITIAL_CELL_COUNT; i++) {
        Cell cell(initialState[i][0], initialState[i][1]);
        mAliveCells.push_back(cell);
    }
}

void LifeSimulator::update(void) {
    int i;
        
    for (i = 0; i < mAliveCells.size(); i++) {
        findAliveNeighbors(mAliveCells[i]);
            
        if (mAliveCells[i].getAliveNeighbors() < 2 || mAliveCells[i].getAliveNeighbors() > 3) {
            mNewlyDeadCells.push_back(mAliveCells[i]);
        }
            
        mAliveCells[i].resetAliveNeighbors();
    } 
        
    for (i = 0; i < mNeighboringDeadCells.size(); i++) {
        if (mNeighboringDeadCells[i].getAliveNeighbors() == 3) {
            mNeighboringDeadCells[i].resetAliveNeighbors();
            mAliveCells.push_back(mNeighboringDeadCells[i]);
        }
    }

    for (i = 0; i < mNewlyDeadCells.size(); i++) {
        for (int j = 0; j < mAliveCells.size(); j++) {
            if (mNewlyDeadCells[i] == mAliveCells[j]) {
                mAliveCells.remove(j);
            }
        }
    }

    mNeighboringDeadCells.clear();
    mNewlyDeadCells.clear();
}

void LifeSimulator::draw(Renderer* renderer) {
    for (int i = 0; i < mAliveCells.size(); i++) {
        renderer->rectangle(
            mAliveCells[i].x(),
            mAliveCells[i].y(),
            mAliveCells[i].width(),
            mAliveCells[i].height(),
            mAliveCells[i].color()
        ); 
    }
}

void LifeSimulator::findAliveNeighbors(Cell& cell) {
    for (int i = 0; i < NEIGHBOR_COUNT; i++) {
        Cell neighbor(cell.x() + neighborState[i][0], cell.y() + neighborState[i][1]);

        // Check grid borders
        if (neighbor.x() < 0 || neighbor.y() < 0 || neighbor.x() >= 312 || neighbor.y() >= 192)
            continue;
        
        checkNeighbor(cell, neighbor);
    }
}

 void LifeSimulator::checkNeighbor(Cell& currentAlive, Cell& neighbor) {
    int found = 0;

    for (int i = 0; i < mAliveCells.size(); i++) {
        if (mAliveCells[i] == neighbor) {
            currentAlive.incrementAliveNeighbors();
            found = 1;
        }
    }

    if (!found) {
        for (int i = 0; i < mNeighboringDeadCells.size(); i++) {
            if (mNeighboringDeadCells[i] == neighbor) {
                found = 1;
                mNeighboringDeadCells[i].incrementAliveNeighbors();
                break;
            }
        }

        if (!found) {
            neighbor.incrementAliveNeighbors();
            mNeighboringDeadCells.push_back(neighbor);
        }
    }  
}