#ifndef OBJECTS_H
#define OBJECTS_H
#ifndef SDL_INCLUDED
    #define SDL_INCLUDED
    #ifdef __linux__
        #include <SDL2/SDL.h>   
    #endif
    #ifdef _WIN32
        #include <SDL.h>
    #endif
#endif

#include "Defines.h"

typedef unsigned char octet;

//void SetupColor();

typedef enum Mode
{
    AUTO, //La génération se fait toute seul
    MANUEL //La génération se fait au clic de souris
}Mode;

//Les différents éléments disponibles 
typedef enum Element
{
    VOID,    //Rien, le vide, le néant
    SAND,    //Sable, placable
    LIQUID,  //Liquide, placable
    SOLID,   //Solide, ne peut pas bouger, placable
    FLOOR,   //Le sol, indestructible
    WOOD,    //Le bois, ne peut pas bouger, flammable
    FIRE,    //LE FEU
    SMOKE,    //La fumée, du liquide à l'envers
    ELEMENT_COUNTER, //enum counter
}Element;

//Chaque Particule est associé à un pixel selon sa position dans l'écran
typedef struct Particule
{
    Element element; //L'élément de la particule
    int pos_x_norm; //Sa position x normalisé, cad divisé par la largeur de la particule
    int pos_y_norm; //Sa position y normalisé, cad divisé par la hauteur de la particule
    uint8_t height; //Devrait être PARTICULE_SIZE
    uint8_t width;  //Devrait être PARTICULE_SIZE
    int ID;  //Son ID unique 
    int update_counter; //Compte le nombre de fois que la particule a été update, peut ne pas être utilisé
    SDL_Rect box; //Son hit box, qui sert aussi au rendu
    SDL_bool hasbeenupdated; //True si la particule a été update durant la boucle d'update, empêche de l'update plusieurs fois
    struct Particule* next;
    struct Particule* previous;
}Particule;

//Représente chaque pixel normalisé (5x5) de la grille 
typedef struct pixel
{
    //int ID; //L'ID unique du pixel, doit être PARTICULE_MAX+1 si element = void
    Particule* part; //Particule utilisé par le pixel, NULL si vide
    Element element; //L'élément associé au pixel
}pixel;

//Scene
extern pixel** grille; //La grille de jeu
//extern Particule Particules[PARTICULE_MAX]; //On déclare nos Particules, selon le nombre maxi choisi
extern Particule* part_header;
extern SDL_Rect FloorAndWall[GRID_WIDTH+GRID_HEIGHT]; //The floor and the wall, duh
//SDL_Rect WaterSelection[SELECTION_SIZE*SELECTION_SIZE]; //The water box selection menu

#endif