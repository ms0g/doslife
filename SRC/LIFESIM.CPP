#include "LIFESIM.H"
#include "RENDERER.H"
#include "STATES.H"

LifeSimulator::LifeSimulator() {
    mAliveCells.reserve(INITIAL_CELL_COUNT);
    
    for (int i = 0; i < INITIAL_CELL_COUNT; i++) {
        Cell cell;
        cellInit(&cell, initialState[i][0], initialState[i][1], CELL_WIDTH, CELL_HEIGHT, CELL_COLOR);
        mAliveCells.push_back(cell);
    }
}

void LifeSimulator::update(void) {
    int i;
        
    for (i = 0; i < mAliveCells.size(); i++) {
        findAliveNeighbors(&mAliveCells[i]);
            
        if (mAliveCells[i].aliveNeighbors < 2 || mAliveCells[i].aliveNeighbors > 3) {
            mNewlyDeadCells.push_back(mAliveCells[i]);
        }
            
        mAliveCells[i].aliveNeighbors = 0;
    } 
        
    for (i = 0; i < mNeighboringDeadCells.size(); i++) {
        if (mNeighboringDeadCells[i].aliveNeighbors == 3) {
            mNeighboringDeadCells[i].aliveNeighbors = 0;
            mAliveCells.push_back(mNeighboringDeadCells[i]);
        }
    }

    for (i = 0; i < mNewlyDeadCells.size(); i++) {
        for (int j = 0; j < mAliveCells.size(); j++) {
            if (checkEquality(&mNewlyDeadCells[i], &mAliveCells[j])) {
                mAliveCells.remove(j);
            }
        }
    }

    mNeighboringDeadCells.clear();
    mNewlyDeadCells.clear();
}

void LifeSimulator::draw(void) {
    for (int i = 0; i < mAliveCells.size(); i++) {
        rectangle(
            mAliveCells[i].x,
            mAliveCells[i].y,
            mAliveCells[i].width,
            mAliveCells[i].height,
            mAliveCells[i].color
        ); 
    }
}

void LifeSimulator::findAliveNeighbors(Cell* cell) {
    for (int i = 0; i < NEIGHBOR_COUNT; i++) {
        Cell neighbor;
        cellInit(&neighbor, cell->x + neighborState[i][0], cell->y + neighborState[i][1], CELL_WIDTH, CELL_HEIGHT, CELL_COLOR);

        // Check grid borders
        if (neighbor.x < 0 || neighbor.y < 0 || neighbor.x >= 312 || neighbor.y >= 192)
            continue;
        
        checkNeighbor(cell, &neighbor);
    }
}

 void LifeSimulator::checkNeighbor(Cell* currentAlive, Cell* neighbor) {
    int i;
    
    for (i = 0; i < mAliveCells.size(); i++) {
        if (checkEquality(&mAliveCells[i], neighbor)) {
            currentAlive->aliveNeighbors++;
            return;
        }
    }

    for (i = 0; i < mNeighboringDeadCells.size(); i++) {
        if (checkEquality(&mNeighboringDeadCells[i], neighbor)) {
            mNeighboringDeadCells[i].aliveNeighbors++;
            return;
        }
    }

    neighbor->aliveNeighbors++;
    mNeighboringDeadCells.push_back(*neighbor);
}