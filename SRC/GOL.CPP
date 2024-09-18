#include "GOL.H"
#include "RENDERER.H"

GOL::GOL() {
    mAliveCells.reserve(21);
    
    Cell c(9, 182);
    mAliveCells.push_back(c);
    c.setX(18);
    mAliveCells.push_back(c);
    c.setX(27);
    mAliveCells.push_back(c);
    c.setX(18);
    c.setY(173);
    mAliveCells.push_back(c);
    c.setX(27);
    mAliveCells.push_back(c);
    c.setX(36);
    mAliveCells.push_back(c);
 
    c.setX(104);
    c.setY(50);
    mAliveCells.push_back(c);
    c.setY(59);
    mAliveCells.push_back(c);
    c.setY(68);
    mAliveCells.push_back(c);
    c.setY(77);
    c.setX(113);
    mAliveCells.push_back(c);
    c.setY(86);
    c.setX(122);
    mAliveCells.push_back(c);
    c.setX(131);
    mAliveCells.push_back(c);
    c.setX(113);
    c.setY(41);
    mAliveCells.push_back(c);
    c.setX(122);
    c.setY(32);
    mAliveCells.push_back(c);
    c.setX(131);
    mAliveCells.push_back(c);

    c.setX(302);
    c.setY(41);
    mAliveCells.push_back(c);
    c.setX(293);
    mAliveCells.push_back(c);
    c.setX(284);
    mAliveCells.push_back(c);
    c.setX(293);
    c.setY(50);
    mAliveCells.push_back(c);
    c.setX(284);
    mAliveCells.push_back(c);
    c.setX(275);
    mAliveCells.push_back(c);
}

void GOL::update(void) {
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

void GOL::draw(Renderer* renderer) {
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

void GOL::findAliveNeighbors(Cell& cell) {
    // right neighbor
    Cell neighbor(cell.x()+9, cell.y());
    checkNeighbor(cell, neighbor);
    
    // left neighbor
    neighbor.setX(cell.x()-9);
    checkNeighbor(cell, neighbor);
    
    // top neighbor
    neighbor.setX(cell.x());
    neighbor.setY(cell.y()-9);
    checkNeighbor(cell, neighbor);
    
    // bottom neighbor
    neighbor.setY(cell.y()+9);
    checkNeighbor(cell, neighbor);
    
    // top right neighbor
    neighbor.setX(cell.x()+9);
    neighbor.setY(cell.y()-9);
    checkNeighbor(cell, neighbor);
   
    // top left neighbor
    neighbor.setX(cell.x()-9);
    neighbor.setY(cell.y()-9);
    checkNeighbor(cell, neighbor);
   
    // bottom right neighbor
    neighbor.setX(cell.x()+9);
    neighbor.setY(cell.y()+9);
    checkNeighbor(cell, neighbor);
    
    // bottom left neighbor
    neighbor.setX(cell.x()-9);
    neighbor.setY(cell.y()+9);
    checkNeighbor(cell, neighbor);
}

 void GOL::checkNeighbor(Cell& currentAlive, Cell& neighbor) {
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

        neighbor.resetAliveNeighbors();
    }  
 }