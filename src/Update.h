#ifndef UPDATE_H
#define UPDATE_H
#ifndef SDL_INCLUDED
    #define SDL_INCLUDED
    #ifdef __linux__
        #include <SDL2/SDL.h>
    #endif
    #ifdef _WIN32
        #include <SDL.h>
    #endif
#endif
#ifndef STDLIB_INCLUDED
    #define STDLIB_INCLUDED
    #include <stdio.h>
    #include <stdlib.h>
#endif
#include "Defines.h"
#include "Objects.h"
#include "Utils.h"

//Called each frame to check if a particule should be created, creates it if so.
extern void UpdateParticulesNumber(Mode, pixel**, Particule[PARTICULE_MAX], Element element_param);

/*This function updates the particule associated with the x and y coordinate, 
should be called in a nested for loop so that it can go through every cell.
The x and y coordinates should be the normalized coord (5x5).
*/
extern void UpdateParticule(int x, int y, pixel**, Particule[PARTICULE_MAX]);

//Draw the Water selection menu to the coord x and y.
extern void DrawWaterSelection(int , int, SDL_Rect[SELECTION_SIZE*SELECTION_SIZE]);

//Créé le sol
extern void CreateFloor(pixel**, SDL_Rect[GRID_WIDTH+GRID_HEIGHT]);

//Affiche le curseur cube
extern void UpdateCursor(SDL_Renderer**);
#endif