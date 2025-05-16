#include "RENDERER.H"
#include "KEYBRD.H"
#include "STATES.H"
#include "VGA.H"
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
           ca_pushback(&newlyDeadCells, *cell);
        }
            
        cell->aliveNeighborsCount = 0;
    } 
        
    for (i = 0; i < neighboringDeadCells.count; i++) {
        cell = ca_at(&neighboringDeadCells, i);
        
        if (cell->aliveNeighborsCount == 3) {
            cell->aliveNeighborsCount = 0;
            ca_pushback(&aliveCells, *cell);
        }
    }

    for (i = 0; i < newlyDeadCells.count; i++) {
        Cell* deadCell = ca_at(&newlyDeadCells, i);

        for (j = 0; j < aliveCells.count; j++) {
            Cell* aliveCell = ca_at(&aliveCells, j);
            
            if (cell_is_equal(deadCell, aliveCell)) {
                ca_remove(&aliveCells, j);
            }
        }
    }

    ca_clear(&neighboringDeadCells);
    ca_clear(&newlyDeadCells);
}

static void render(void) {
    int i;

    rnd_clear(BLACK);

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
        cell_init(&neighbor, cell->x + neighborState[i][0], cell->y + neighborState[i][1], CELL_WIDTH, CELL_HEIGHT, CELL_COLOR);

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
        
        if (cell_is_equal(cell, neighbor)) {
            currentAlive->aliveNeighborsCount++;
            return;
        }
    }

    for (i = 0; i < neighboringDeadCells.count; i++) {
        cell = ca_at(&neighboringDeadCells, i);
        
        if (cell_is_equal(cell, neighbor)) {
            cell->aliveNeighborsCount++;
            return;
        }
    }

    neighbor->aliveNeighborsCount++;
    ca_pushback(&neighboringDeadCells, *neighbor);
}

static void initialize_cells(void) {
    int i;
    ca_init(&aliveCells, INITIAL_CELL_COUNT);
    ca_init(&neighboringDeadCells, 1);
    ca_init(&newlyDeadCells, 1);
    
    for (i = 0; i < INITIAL_CELL_COUNT; i++) {
        Cell cell;
        cell_init(&cell, initialState[i][0], initialState[i][1], CELL_WIDTH, CELL_HEIGHT, CELL_COLOR);
        ca_pushback(&aliveCells, cell);
    }
}
 
void main(void) {
    isRunning = 1;

    vga_init();
    kb_init();

    initialize_cells();
    
    while (isRunning) {
        process_input();
        update();
        render();
    }

    vga_exit();
    kb_exit();
}


