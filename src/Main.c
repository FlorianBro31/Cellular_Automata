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
    #endif
    #ifdef _WIN32
        //gcc.exe -Wall -std=c17 -g .\src\Main.c .\src\Debug.c .\src\Update.c .\src\Utils.c .\src\Texte.c -I.\include -L.\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o .\bin\game
        #include <time.h>
        #include <SDL.h>
        #include "SDL_ttf.h"
    #endif
#endif

#include <time.h>

#include "Defines.h"
#include "Objects.h"
#include "Debug.h"
#include "Utils.h"
#include "Update.h"
#include "Texte.h"


int main(int argc, char* argv[])
{
    SDL_Window* fenetre = NULL; //La fenêtre
    SDL_Renderer* renderer = NULL; //Le renderer
    SDL_Event event; //Là où les events SDL sont stockés
    Init(&fenetre, &renderer); //On init plein de trucs
    InitTexte();
    time_t t;
    //-----Init de la fonction rand()------
    srand((unsigned int) time(&t));
    //-------------------------------------
    ClearGrid(grille);
    //Créé le sol
    CreateFloor(grille, FloorAndWall);
    SDL_ShowCursor(SDL_DISABLE);//On disable le curseur pour pouvoir créer le nôtre à partir des SDL_Rect
    while(programRunnig)//Boucle "infini" du jeu
    {
        starting_tick = SDL_GetTicks();//Utile pour cap les fps
        if(!FrameByFrameMode)
            frame_count++;//Comptage des frames, pas utile pour cap les fps mais pour créer de particules toutes les x frames
        if(!Pause)
        {
            UpdateParticulesNumber(MANUEL, grille, Particules, element_param);//Check if a particule has to be created
            if(!FrameByFrameMode)
            {                   //-1-1 so as to avoid updating the floor, which would be pointless
                for(int y = GRID_HEIGHT-2; y>=0; y = y-1)//On parcourt la grille toute les frames
                {
                    for(int x = GRID_WIDTH-1; x>= 0; x = x-1)
                    {
                        if(grille[y][x].element != VOID && grille[y][x].element != SOLID)//Il y a un truc qui peut bouger
                        {
                            UpdateParticule(x, y, grille, Particules);//Update le truc
                        }
                    }
                }
                for (int i = 0; i < current_particule; i++)
                {
                    Particules[i].hasbeenupdated = SDL_FALSE;
                }
            }
        }
        while(SDL_PollEvent(&event)) //Si un event a été détecté
        {            
            switch (event.type) //On gère tous les event via une switch, pas sûr que ce soit la meilleure idée,
            {                   //on verra si ça se complique plus tard, ça peut vite devenir bordelique
            case SDL_QUIT: //On veut quitter le programme
                programRunnig = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN://Front montant du clique
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT: //Clique gauche
                        SDL_GetMouseState(&Mouse_x, &Mouse_y);
                        if((Mouse_x < TO_PIXEL_SIZE(GRID_WIDTH)) && (Mouse_y < TO_PIXEL_SIZE(GRID_HEIGHT)))//On clique dans l'écran principale
                        {
                            if(event.button.state == SDL_PRESSED )//On veut créer une particule
                            {
                                MousePressed = ParticuleToBeCreated = SDL_TRUE;
                            }
                        }
                        else //On ne clique pas dans l'écran principale
                        {
                            ParticuleToBeCreated = SDL_FALSE; 
                        }
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP: //Front descendant du clique
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT: //clique gauche
                        if(event.button.state == SDL_RELEASED) //On ne veut plus créer de particule
                        {
                            MousePressed = ParticuleToBeCreated = SDL_FALSE;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_F1:
                        if(!Help)//Load
                            HelpMenuLoadUnload(LOAD);
                        else if(Help)//Unload
                            HelpMenuLoadUnload(UNLOAD);
                        Pause = SDL_TRUE;
                        Help = !Help;
                        break;
                    case SDLK_1:
                        element_param = SAND;
                        break;
                    case SDLK_2:
                        element_param = LIQUID;
                        break;
                    case SDLK_3:
                        element_param = SOLID;
                        break;
                    case SDLK_4:
                        element_param = WOOD;
                        break;
                    case SDLK_5:
                        element_param = FIRE;
                        break;
                    case SDLK_SPACE:
                        if(!FrameByFrameMode && !Help)
                            Pause = !Pause;
                        break;
                    case SDLK_p:
                        PrintGrille(grille);
                        printf("Printed\n");
                        break;
                    case SDLK_x:
                        ParticuleToBeDestroyed = !ParticuleToBeDestroyed;
                        break;
                    case SDLK_f:
                        if(!Pause)
                            FrameByFrameMode = !FrameByFrameMode;
                        break;
                    case SDLK_RIGHT:
                    {
                        if(FrameByFrameMode && !Pause)
                        {
                            frame_count++;
                            for(int y = GRID_HEIGHT-2; y>=0; y = y-1)//On parcourt la grille toute les frames (en évitant le sol)
                            {
                                for(int x = GRID_WIDTH-1; x>= 0; x = x-1)//(int x = 0; x<160; x = x+1)
                                {
                                    if(grille[y][x].element != VOID && grille[y][x].element != SOLID)//Il y a un truc qui peut bouger
                                    {
                                        UpdateParticule(x, y, grille, Particules);//Update le truc
                                    }
                                }
                            }
                            for (int i = 0; i < current_particule; i++)
                            {
                                Particules[i].hasbeenupdated = SDL_FALSE;
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
                break;
            case SDL_MOUSEWHEEL:
                if(event.wheel.y > 0)//Scroll up
                {
                    //Change size of the cursor to a bigger one
                    cursor_pad+=PARTICULE_SIZE;

                }
                else if(event.wheel.y < 0) //Scroll down
                {
                    //Change size of the cursor to a smaller one
                    if(cursor_pad != 0)
                        cursor_pad-=PARTICULE_SIZE;
                }
                break;
            default:
                break;
            }
            SDL_GetMouseState(&Mouse_x, &Mouse_y);
            /* 
            *On check si l'utilisateur maintient la souris enfoncée dans l'espace menu et on désactive 
            *la création de particule si tel est le cas.
            *J'arrive pas à le faire dans la switch, donc c'est ici pour l'instant =(
            */
            if((Mouse_x > TO_PIXEL_SIZE(GRID_WIDTH)) || (Mouse_y > TO_PIXEL_SIZE(GRID_HEIGHT)))
            {
                ParticuleToBeCreated = SDL_FALSE;
            }
        }
        
        //On clear le renderer
        if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0){ExitWithError("SDL_RenderDrawColor");}
        if(SDL_RenderClear(renderer) != 0){ExitWithError("SDL_RenderClear");}

        //Rendu du floor et du mur
        if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0 ){ExitWithError("SDL_RenderDrawColor");}
        if(SDL_RenderFillRects(renderer, FloorAndWall, (GRID_HEIGHT+GRID_WIDTH)) != 0 ){ExitWithError("SDL_RenderFillRects");}

        //Rendu des particules
        for(int i = 0; i<current_particule; i++)
        {
            switch (Particules[i].element)
            {
            case SAND:
                if(SDL_SetRenderDrawColor(renderer, ColorSand.r, ColorSand.g, ColorSand.b, ColorSand.a) != 0){ExitWithError("SDL_RenderDrawColor_SAND");}
                break;
            case LIQUID:
                if(SDL_SetRenderDrawColor(renderer, ColorWater.r, ColorWater.g, ColorWater.b, ColorWater.a) != 0){ExitWithError("SDL_RenderDrawColor_LIQUID");}
                break;
            case SOLID:
                if(SDL_SetRenderDrawColor(renderer, ColorConcrete.r, ColorConcrete.g, ColorConcrete.b, ColorConcrete.a) != 0){ExitWithError("SDL_RenderDrawColor_SOLID");}
                break;
            case WOOD:
                if(SDL_SetRenderDrawColor(renderer, ColorWood.r, ColorWood.g, ColorWood.b, ColorWood.a) != 0){ExitWithError("SDL_RenderDrawColor_WOOD");}
                break;
            case FIRE:
                if(SDL_SetRenderDrawColor(renderer, ColorFire.r, ColorFire.g, ColorFire.b, ColorFire.a) != 0){ExitWithError("SDL_SetRenderDrawColor_FIRE");}
                break;
            case SMOKE:
                if(SDL_SetRenderDrawColor(renderer, ColorSmoke.r, ColorSmoke.g, ColorSmoke.b, ColorSmoke.a) != 0){ExitWithError("SDL_SetRenderDrawColor_SMOKE");}
                break;
            default:
                ExitWithError("Particule with Error Element detected");
                break;
            }
            if(SDL_RenderFillRect(renderer, &Particules[i].box) != 0){ExitWithError("SDL_RenderFillRect");}
        }
        //Rendu du curseur
        UpdateCursor(&renderer);
        //Rendu des textes
        UpdateTexteNumberParticules(current_particule, &renderer);
        if(Pause)
            PrintPause(&renderer);
        if(FrameByFrameMode)
            PrintFrameByFrameMode(&renderer);
        if(Help)
            PrintHelpMenu(&renderer);
        PrintAddOrDeleteMode(&renderer);
        //On dessine le tout
        SDL_RenderPresent(renderer);

        FrameCap(starting_tick, SIMULATION_SPEED);//Cap les fps à 60
        if(frame_count >20)//Prevents overflowing if user isn't doing anything
        {
            frame_count = 0;
        }
    }

    //Quitte l'application proprement
    TTF_CloseFont(Sans);
    TTF_Quit();
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        free(grille[i]);
        grille[i] = NULL;
    }
    free(grille);
    grille = NULL;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();//Libère les ressources allouées à l'application
    printf("SDL uninitialized successfully !\n");
    return EXIT_SUCCESS; //return 0
}
