#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>
#include "GRAPHICS.H"
#include "VECTOR.H"

enum CellState {
    DEAD,
    ALIVE
};

class Cell: public Rectangle {
public:
    Cell(): Rectangle(0, 0, 0, 0, 0) {
        m_state =DEAD;
        m_aliveNeighbors = 0;
    }
    Cell(int x, int y, int width, int height, char color): Rectangle(x, y, width, height, color) {
        m_state = ALIVE;
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

    int getState(void) {
        return m_state;
    }

    void setState(int state) {
        m_state = state;
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
    int m_state;
    int m_aliveNeighbors;
};

void findNeigh(Cell &current, Cell &neigh, vector<Cell> &aliveCells, vector<Cell> &deadCells);

void findALiveNeighbors(Cell &cell, vector<Cell> &aliveCells, vector<Cell> &deadCells);

void main(void) {   
    initGFM();

    vector<Cell> aliveCells(3);
    vector<Cell> deadCells;

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
        for (i = 0; i < aliveCells.size(); i++) {
            findALiveNeighbors(aliveCells[i], aliveCells, deadCells);
            if (aliveCells[i].getAliveNeighbors() < 2 || aliveCells[i].getAliveNeighbors() > 3) {
                aliveCells[i].setState(DEAD);
            }
            aliveCells[i].resetAliveNeighbors();
        } 

        vector<Cell> tobeRemovedCells;
        for (i = 0; i < aliveCells.size(); i++) {
            if (aliveCells[i].getState() == DEAD) {
                aliveCells[i].hide();
                tobeRemovedCells.push_back(aliveCells[i]);
            }
            
        }
        
        for (i = 0; i < deadCells.size(); i++) {
            if (deadCells[i].getAliveNeighbors() == 3) {
                deadCells[i].setState(ALIVE);
                deadCells[i].resetAliveNeighbors();
                aliveCells.push_back(deadCells[i]);
                deadCells[i].show();
            }
        }

        for (i = 0; i < tobeRemovedCells.size(); i++) {
            for (int j = 0; j < aliveCells.size(); j++) {
                if (tobeRemovedCells[i] == aliveCells[j]) {
                    aliveCells.remove(j);
                }
            }
        }

        deadCells.clear();
        delay(100);

    }
}


void findNeigh(Cell &current, Cell &neigh, vector<Cell> &aliveCells, vector<Cell> &deadCells) {
    bool found = true;
    for (int i = 0; i < aliveCells.size(); i++) {
        if (aliveCells[i] == neigh) {
            current.incrementAliveNeighbors();
            return;
        } else {
            found = false;
        }
    }
    if (!found) {
        for (int i = 0; i < deadCells.size(); i++) {
            if (deadCells[i] == neigh) {
                found = true;
                deadCells[i].incrementAliveNeighbors();
                break;
            }
        }
        if (!found) {
            neigh.setState(DEAD);
            neigh.incrementAliveNeighbors();
            deadCells.push_back(neigh);
        }
    }

    neigh.setState(ALIVE);
    neigh.resetAliveNeighbors();
}

void findALiveNeighbors(Cell &current, vector<Cell> &aliveCells, vector<Cell> &deadCells) {
    // right neighbor
    Cell neigh(current.getX()+9, current.getY(), 8, 8, GREEN);
    findNeigh(current, neigh, aliveCells, deadCells);
    
    // left neighbor
    neigh.setX(current.getX()-9);
    findNeigh(current, neigh, aliveCells, deadCells);
    
    // top neighbor
    neigh.setX(current.getX());
    neigh.setY(current.getY()-9);
    findNeigh(current, neigh, aliveCells, deadCells);
    
    // bottom neighbor
    neigh.setY(current.getY()+9);
    findNeigh(current, neigh, aliveCells, deadCells);
    
    // top right neighbor
    neigh.setX(current.getX()+9);
    neigh.setY(current.getY()-9);
    findNeigh(current, neigh, aliveCells, deadCells);
   
    // top left neighbor
    neigh.setX(current.getX()-9);
    neigh.setY(current.getY()-9);
    findNeigh(current, neigh, aliveCells, deadCells);
   
    // bottom right neighbor
    neigh.setX(current.getX()+9);
    neigh.setY(current.getY()+9);
    findNeigh(current, neigh, aliveCells, deadCells);
    
    // bottom left neighbor
    neigh.setX(current.getX()-9);
    neigh.setY(current.getY()+9);
    findNeigh(current, neigh, aliveCells, deadCells);
            
}