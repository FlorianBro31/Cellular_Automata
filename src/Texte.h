#ifndef TEXTE_H
#define TEXTE_H
#ifndef STDLIB_INCLUDED
    #define STDLIB_INCLUDED
    #include <stdio.h>
    #include <stdlib.h>
#endif
#ifndef SDL_INCLUDED
    #define SDL_INCLUDED
    #ifdef __linux__
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>
        #define ARIAL "./assets/fonts/arial.ttf"
    #endif
    #ifdef _WIN32
        #include <SDL.h>
        #include "SDL_ttf.h"
        #define ARIAL "C:/windows/fonts/arial.ttf"
    #endif
#endif
#include "Defines.h"
#include "Utils.h"

extern TTF_Font* Sans;

//Init tout les trucs nécéssaires au texte
extern void InitTexte();
//Update the text displaying the current number of particule
extern void UpdateTexteNumberParticules(int, SDL_Renderer**);
//Displays the pause message
extern void PrintPause(SDL_Renderer**);
//Displays the FrameByFrame mode message
extern void PrintFrameByFrameMode(SDL_Renderer**);
//Displays the current Add/Delete mode
extern void PrintAddOrDeleteMode(SDL_Renderer**);
//Load or unload memory for the help menu
extern void HelpMenuLoadUnload(int);
//Display the help menu
extern void PrintHelpMenu(SDL_Renderer**);

#endif
