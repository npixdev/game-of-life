# Conway's Game of Life — C Implementation

A high-performance, terminal-based implementation of Conway's Game of Life written in C. This project focuses on efficient memory management, low-level system optimization, and mathematical grid logic.

---

## Features

- **Dynamic Memory Management** — Uses heap allocation (`malloc`/`free`) to handle arbitrary grid sizes defined at runtime, moving away from static compile-time constraints.
- **Torus World Logic** — Implements modular arithmetic to create a seamless, wrapping universe. Cells exiting the boundary reappear on the opposite side, simulating a finite but unbounded plane.
- **Win32 Console Optimization** — High-speed rendering using the `SetConsoleCursorPosition` API to eliminate screen flickering common with standard buffer clearing commands.
- **Double Buffering** — Employs two discrete state matrices (current and next) to ensure calculation integrity during generational transitions.

---

## Technical Details

### Memory Architecture

The grid is implemented as a pointer-to-pointer (`int**`), allowing for a flexible 2D array structure. Memory usage scales with the input configuration.
```c
int** table = (int**)malloc(rows * sizeof(int*));
for (int i = 0; i < rows; i++) {
    table[i] = (int*)malloc(cols * sizeof(int));
}
```

### Boundary Physics

To avoid edge death and simulate an unbounded space within a finite grid, the neighbor-counting algorithm wraps coordinates using the modulo operator:
```
ni = (i + di + rows) % rows
nj = (j + dj + cols) % cols
```

---

## Usage

**1. Compile**
```bash
gcc life.c -o life.exe
```

**2. Configure**

Create or edit `glider.txt`. The first line must contain the grid dimensions, followed by the cell state matrix:
```
20 20
0 1 0 0 ...
```

**3. Run**

Execute `life.exe` and select the **Load** option from the menu.

---

## Requirements

- Windows (uses Win32 Console API)
- GCC or any C99-compatible compiler
