#ifndef DEBUG_H
#define DEBUG_H

#ifndef STDLIB_INCLUDED
    #define STDLIB_INCLUDED
    #include <stdio.h>
    #include <stdlib.h>
#endif
#include "Objects.h"

//Debug function, prints the grid.
extern void PrintGrille(pixel**);

#endif