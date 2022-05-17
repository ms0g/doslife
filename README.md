# doslife

16-bit real mode implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).


![doslife](ASSETS/doslife.gif)

### Prerequisites
+ Turbo C++ (>= 3.0)
+ Turbo Assembler (>= 3.2)
+ DOSBox or a real DOS computer

### Building
```bash
C:\>MAKE.EXE
```
or
```
C:\>TCC.EXE -c -oGRAPHICS.OBJ SRC/GRAPHICS.CPP
C:\>TCC.EXE SRC/MAIN.CPP GRAPHICS.OBJ
```

### Run
```bash
C:\>MAIN.EXE
```

