#ifndef UTILS_H
#define UTILS_H
#ifndef SDL_INCLUDED
    #define SDL_INCLUDED
    #ifdef __linux__
        #include <SDL2/SDL.h>   
    #endif
    #ifdef _WIN32
        #include <SDL.h>
    #endif
#ifndef STDLIB_INCLUDED
    #define STDLIB_INCLUDED
    #include <stdio.h>
    #include <stdlib.h>
#endif
#endif
#include "Defines.h"
#include "Objects.h"

//TODO: union flag
extern SDL_bool ParticuleToBeCreated; //*flag : une particule doit être créée
extern SDL_bool ParticuleToBeDestroyed; //*flag : une particule doit être détruite
extern SDL_bool FrameByFrameMode; //*flag : Mode frame by frame
extern SDL_bool Help; //*flag : help
extern int current_particule; //Traque le nombre de particule présentes
extern int frame_count; //Traque le nombre de frame, on commence à 9 pour arriver à 10 et créer une particule lors de la 1ère frame
extern int cursor_pad; //Deals with the size of the cursor

extern Element element_param; //Quel élément on veut créer lors d'un clic de souris
extern SDL_bool Pause; //Pause flag
extern Uint32 starting_tick; //Utile à la fonction FrameCap
extern SDL_bool programRunnig; //Si faux -> le programme s'arrête (proprement)
extern SDL_bool MousePressed; //Pas très utile pour l'instant, on verra par la suite

extern int Mouse_x, Mouse_y; //Les coordonnées de la souris
//Couleurs
extern SDL_Color ColorSand; //La couleur du sable
extern SDL_Color ColorWater; //La couleur de l'eau
extern SDL_Color Blanc; //Blanc
extern SDL_Color ColorConcrete; //La couleur du béton
extern SDL_Color Blanc_casse; //Blanc cassé
extern SDL_Color ColorWood; //La couleur du bois
extern SDL_Color ColorFire; //La couleur du feu
extern SDL_Color ColorSmoke; //La couleur de la fumée

//Prints an error message and exits the program.
extern void ExitWithError(const char*);

//Initialize the whole SDL framework, will have more parameters in the future.
extern void Init(SDL_Window**, SDL_Renderer**);

//Call this function each frame to set the desired max fps.
extern void FrameCap(Uint32 ,int);

//Fills the grid with VOID
extern void ClearGrid();

//Add a particule to the linked list of parts
extern Particule* AddParticule();

//Remove a particule from the list, also update grille
extern void DeleteParticule(Particule* part_to_delete);

#endif