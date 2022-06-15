#include <iostream.h>
#include <stdlib.h>
#include <dos.h>
#include "GRAPHICS.H"
#include "VECTOR.H"
#include "BOOL.H"


class Cell: public Rectangle {
public:
    Cell(): Rectangle(0, 0, 0, 0, 0) {
        m_aliveNeighbors = 0;
    }
    
    Cell(int x, int y, int width, int height, char color): Rectangle(x, y, width, height, color) {
        m_aliveNeighbors = 0;
    }

    void show(void) {
        setColor(GREEN);
        draw();
    }
    void hide(void) {
        setColor(BLACK);
        draw();
    }
    void moveTo(int x, int y) {
        hide();
        setX(x);
        setY(y);
        show();
    }

    int getAliveNeighbors(void) {
        return m_aliveNeighbors;
    }

    void resetAliveNeighbors(void) {
        m_aliveNeighbors = 0;
    }

    void incrementAliveNeighbors(void) {
        m_aliveNeighbors++;
    }

    bool operator==(const Cell &other){ 
        return (bool)(this->getX() == other.getX() && this->getY() == other.getY());
    }
    
    bool operator!=(const Cell &other){ 
        return (bool)(this->getX() != other.getX() || this->getY() != other.getY());
    }

private:
    int m_aliveNeighbors;
};

void checkIf(Cell &current, Cell &neigh, vector<Cell> &aliveCells, vector<Cell> &neighboringDeadCells);

void findAliveNeighbors(Cell &cell, vector<Cell> &aliveCells, vector<Cell> &neighboringDeadCells);

void main(void) {   
    initGFM();

    vector<Cell> aliveCells(3);
    vector<Cell> neighboringDeadCells;

    // Create the cells
    Cell c(9, 182, 8, 8, GREEN);
    aliveCells.push_back(c);
    c.setX(18);
    aliveCells.push_back(c);
    c.setX(27);
    aliveCells.push_back(c);
    c.setX(18);
    c.setY(173);
    aliveCells.push_back(c);
    c.setX(27);
    aliveCells.push_back(c);
    c.setX(36);
    aliveCells.push_back(c);
 
    c.setX(104);
    c.setY(50);
    aliveCells.push_back(c);
    c.setY(59);
    aliveCells.push_back(c);
    c.setY(68);
    aliveCells.push_back(c);
    c.setY(77);
    c.setX(113);
    aliveCells.push_back(c);
    c.setY(86);
    c.setX(122);
    aliveCells.push_back(c);
    c.setX(131);
    aliveCells.push_back(c);
    c.setX(113);
    c.setY(41);
    aliveCells.push_back(c);
    c.setX(122);
    c.setY(32);
    aliveCells.push_back(c);
    c.setX(131);
    aliveCells.push_back(c);

    c.setX(302);
    c.setY(41);
    aliveCells.push_back(c);
    c.setX(293);
    aliveCells.push_back(c);
    c.setX(284);
    aliveCells.push_back(c);
    c.setX(293);
    c.setY(50);
    aliveCells.push_back(c);
    c.setX(284);
    aliveCells.push_back(c);
    c.setX(275);
    aliveCells.push_back(c);
   
    for (int i = 0; i < aliveCells.size(); i++) {
        aliveCells[i].show();
    }

    while(true) {
        delay(100);
        int i;
        vector<Cell> newlyDeadCells;
        for (i = 0; i < aliveCells.size(); i++) {
            findAliveNeighbors(aliveCells[i], aliveCells, neighboringDeadCells);
            if (aliveCells[i].getAliveNeighbors() < 2 || aliveCells[i].getAliveNeighbors() > 3) {
                aliveCells[i].hide();
                newlyDeadCells.push_back(aliveCells[i]);
            }
            aliveCells[i].resetAliveNeighbors();
        } 
        
        for (i = 0; i < neighboringDeadCells.size(); i++) {
            if (neighboringDeadCells[i].getAliveNeighbors() == 3) {
                neighboringDeadCells[i].show();
                neighboringDeadCells[i].resetAliveNeighbors();
                aliveCells.push_back(neighboringDeadCells[i]);
            }
        }

        for (i = 0; i < newlyDeadCells.size(); i++) {
            for (int j = 0; j < aliveCells.size(); j++) {
                if (newlyDeadCells[i] == aliveCells[j]) {
                    aliveCells.remove(j);
                }
            }
        }

        neighboringDeadCells.clear();
        delay(100);

    }
}


void checkIf(Cell &current, Cell &neigh, vector<Cell> &aliveCells, vector<Cell> &neighboringDeadCells) {
    bool found = false;
    for (int i = 0; i < aliveCells.size(); i++) {
        if (aliveCells[i] == neigh) {
            current.incrementAliveNeighbors();
            found = true;
        }
    }
    if (!found) {
        for (int i = 0; i < neighboringDeadCells.size(); i++) {
            if (neighboringDeadCells[i] == neigh) {
                found = true;
                neighboringDeadCells[i].incrementAliveNeighbors();
                break;
            }
        }
        if (!found) {
            neigh.incrementAliveNeighbors();
            neighboringDeadCells.push_back(neigh);
        }
        neigh.resetAliveNeighbors();
    }  
}


void findAliveNeighbors(Cell &current, vector<Cell> &aliveCells, vector<Cell> &neighboringDeadCells) {
    // right neighbor
    Cell neigh(current.getX()+9, current.getY(), 8, 8, GREEN);
    checkIf(current, neigh, aliveCells, neighboringDeadCells);
    
    // left neighbor
    neigh.setX(current.getX()-9);
    checkIf(current, neigh, aliveCells, neighboringDeadCells);
    
    // top neighbor
    neigh.setX(current.getX());
    neigh.setY(current.getY()-9);
    checkIf(current, neigh, aliveCells, neighboringDeadCells);
    
    // bottom neighbor
    neigh.setY(current.getY()+9);
    checkIf(current, neigh, aliveCells, neighboringDeadCells);
    
    // top right neighbor
    neigh.setX(current.getX()+9);
    neigh.setY(current.getY()-9);
    checkIf(current, neigh, aliveCells, neighboringDeadCells);
   
    // top left neighbor
    neigh.setX(current.getX()-9);
    neigh.setY(current.getY()-9);
    checkIf(current, neigh, aliveCells, neighboringDeadCells);
   
    // bottom right neighbor
    neigh.setX(current.getX()+9);
    neigh.setY(current.getY()+9);
    checkIf(current, neigh, aliveCells, neighboringDeadCells);
    
    // bottom left neighbor
    neigh.setX(current.getX()-9);
    neigh.setY(current.getY()+9);
    checkIf(current, neigh, aliveCells, neighboringDeadCells);
            
}