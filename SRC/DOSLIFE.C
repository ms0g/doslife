#include "RENDERER.H"
#include "KEYBRD.H"
#include "STATES.H"
#include "CELL.H"

static int is_running;
static CellArray alive_cells;
static CellArray neighboring_dead_cells;
static CellArray newly_dead_cells;

static void process_neighbors(Cell* cell);
static void check_neighbor(Cell* current_alive, Cell* neighbor);

static void process_input(void) {
    char key = kbhit();

    if (key == ESC) {
        is_running = 0;
    }
}

static void update(void) {
    int i,j;
    Cell* cell;
        
    for (i = 0; i < alive_cells.count; i++) {
        cell = ca_at(&alive_cells, i);
        
        process_neighbors(cell);
            
        if (cell->aliveNeighborsCount < 2 || cell->aliveNeighborsCount > 3) {
           ca_pushback(&newly_dead_cells, cell);
        }
            
        cell->aliveNeighborsCount = 0;
    } 
        
    for (i = 0; i < neighboring_dead_cells.count; i++) {
        cell = ca_at(&neighboring_dead_cells, i);
        
        if (cell->aliveNeighborsCount == 3) {
            cell->aliveNeighborsCount = 0;
            ca_pushback(&alive_cells, cell);
        }
    }

    for (i = 0; i < newly_dead_cells.count; i++) {
        Cell* deadCell = ca_at(&newly_dead_cells, i);

        for (j = 0; j < alive_cells.count; j++) {
            Cell* aliveCell = ca_at(&alive_cells, j);
            
            if (CELL_IS_SAME(deadCell, aliveCell)) {
                ca_remove(&alive_cells, j);
            }
        }
    }

    ca_clear(&neighboring_dead_cells);
    ca_clear(&newly_dead_cells);
}

static void render(void) {
    int i;
    Cell* cell;

    rnd_clear(0x0);

    for (i = 0; i < alive_cells.count; i++) {
        cell = ca_at(&alive_cells, i);
        
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

 static void check_neighbor(Cell* current_alive, Cell* neighbor) {
    int i;
    Cell* cell;
    
    for (i = 0; i < alive_cells.count; i++) {
        cell = ca_at(&alive_cells, i);
        
        if (CELL_IS_SAME(cell, neighbor)) {
            current_alive->aliveNeighborsCount++;
            return;
        }
    }

    for (i = 0; i < neighboring_dead_cells.count; i++) {
        cell = ca_at(&neighboring_dead_cells, i);
        
        if (CELL_IS_SAME(cell, neighbor)) {
            cell->aliveNeighborsCount++;
            return;
        }
    }

    neighbor->aliveNeighborsCount++;
    ca_pushback(&neighboring_dead_cells, neighbor);
}

static void initialize_cells(void) {
    int i;
    ca_init(&alive_cells, INITIAL_CELL_COUNT);
    ca_init(&neighboring_dead_cells, 1);
    ca_init(&newly_dead_cells, 1);
    
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
    is_running = 1;

    rnd_init();
    kb_init();

    initialize_cells();
    
    while (is_running) {
        process_input();
        update();
        render();
    }

    ca_free(&alive_cells);
    ca_free(&neighboring_dead_cells);
    ca_free(&newly_dead_cells);

    rnd_exit();
    kb_exit();
}


