#include "RENDERER.H"
#include "KEYBRD.H"
#include "STATES.H"
#include "CELL.H"

static int isRunning;
static CellArray aliveCells;
static CellArray neighboringDeadCells;
static CellArray newlyDeadCells;

static void process_neighbors(Cell* cell);
static void check_neighbor(Cell* currentAlive, Cell* neighbor);

static void process_input(void) {
    char key = kbhit();

    if (key == ESC) {
        isRunning = 0;
    }
}

static void update(void) {
    int i,j;
    Cell* cell;
        
    for (i = 0; i < aliveCells.count; i++) {
        cell = ca_at(&aliveCells, i);
        
        process_neighbors(cell);
            
        if (cell->aliveNeighborsCount < 2 || cell->aliveNeighborsCount > 3) {
           ca_pushback(&newlyDeadCells, cell);
        }
            
        cell->aliveNeighborsCount = 0;
    } 
        
    for (i = 0; i < neighboringDeadCells.count; i++) {
        cell = ca_at(&neighboringDeadCells, i);
        
        if (cell->aliveNeighborsCount == 3) {
            cell->aliveNeighborsCount = 0;
            ca_pushback(&aliveCells, cell);
        }
    }

    for (i = 0; i < newlyDeadCells.count; i++) {
        Cell* deadCell = ca_at(&newlyDeadCells, i);

        for (j = 0; j < aliveCells.count; j++) {
            Cell* aliveCell = ca_at(&aliveCells, j);
            
            if (CELL_IS_SAME(deadCell, aliveCell)) {
                ca_remove(&aliveCells, j);
            }
        }
    }

    ca_clear(&neighboringDeadCells);
    ca_clear(&newlyDeadCells);
}

static void render(void) {
    int i;

    rnd_clear(0x0);

    for (i = 0; i < aliveCells.count; i++) {
        Cell* cell = ca_at(&aliveCells, i);
        
        rnd_rectangle(
            cell->x,
            cell->y,
            cell->width,
            cell->height,
            cell->color
        );
    }

    rnd_update_buffer();
}

static void process_neighbors(Cell* cell) {
    int i;

    for (i = 0; i < NEIGHBOR_COUNT; i++) {
        Cell neighbor;
        neighbor.x = cell->x + neighbor_state[i][0];
        neighbor.y = cell->y + neighbor_state[i][1];
        neighbor.width = CELL_WIDTH;
        neighbor.height = CELL_HEIGHT;
        neighbor.color = CELL_COLOR;
        neighbor.aliveNeighborsCount = 0;
        // Check grid borders
        if (neighbor.x < 0 || neighbor.y < 0 || neighbor.x >= 312 || neighbor.y >= 192)
            continue;
        
        check_neighbor(cell, &neighbor);
    }
}

 static void check_neighbor(Cell* currentAlive, Cell* neighbor) {
    int i;
    Cell* cell;
    
    for (i = 0; i < aliveCells.count; i++) {
        cell = ca_at(&aliveCells, i);
        
        if (CELL_IS_SAME(cell, neighbor)) {
            currentAlive->aliveNeighborsCount++;
            return;
        }
    }

    for (i = 0; i < neighboringDeadCells.count; i++) {
        cell = ca_at(&neighboringDeadCells, i);
        
        if (CELL_IS_SAME(cell, neighbor)) {
            cell->aliveNeighborsCount++;
            return;
        }
    }

    neighbor->aliveNeighborsCount++;
    ca_pushback(&neighboringDeadCells, neighbor);
}

static void initialize_cells(void) {
    int i;
    ca_init(&aliveCells, INITIAL_CELL_COUNT);
    ca_init(&neighboringDeadCells, 1);
    ca_init(&newlyDeadCells, 1);
    
    for (i = 0; i < INITIAL_CELL_COUNT; i++) {
        Cell cell;
        cell.x = initial_state[i][0];
        cell.y = initial_state[i][1];
        cell.width = CELL_WIDTH;
        cell.height = CELL_HEIGHT;
        cell.color = CELL_COLOR;
        cell.aliveNeighborsCount = 0;

        ca_pushback(&alive_cells, &cell);
    }
}
 
void main(void) {
    isRunning = 1;

    rnd_init();
    kb_init();

    initialize_cells();
    
    while (isRunning) {
        process_input();
        update();
        render();
    }

    ca_free(&aliveCells);
    ca_free(&neighboringDeadCells);
    ca_free(&newlyDeadCells);

    rnd_exit();
    kb_exit();
}


