#ifndef DEFINES_H
#define DEFINES_H


#define LOAD 1
#define UNLOAD 0

#define PARTICULE_SIZE 5 //Width = length, should be a square

#define TO_PIXEL_SIZE(x) (x*PARTICULE_SIZE)
#define TO_PARTCULE_SIZE(x) (x/PARTICULE_SIZE)

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700

#define GRID_WIDTH_PAD 20
#define GRID_HEIGHT_PAD 10

#define GRID_WIDTH ((WINDOW_WIDTH/PARTICULE_SIZE) - GRID_WIDTH_PAD)
#define GRID_HEIGHT ((WINDOW_HEIGHT/PARTICULE_SIZE) - GRID_HEIGHT_PAD)

#define PARTICULE_MAX 5000
#define SELECTION_SIZE 10

#endif