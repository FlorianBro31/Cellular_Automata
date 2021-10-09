#include "Utils.h"

//extern SDL_Point Cursor[24];
//! Plein de trucs à mettre en local
//TODO: Trier ce qui doit être local et ce qui n'a pas besoin
SDL_bool ParticuleToBeCreated=SDL_FALSE;
SDL_bool ParticuleToBeDestroyed=SDL_FALSE;
SDL_bool FrameByFrameMode = SDL_FALSE;
int current_particule = 0; //count the number of current particules, and point to the last one, can be used like a Stack Pointer
int frame_count = 9;
Uint32 starting_tick = 0;
SDL_bool programRunnig = SDL_TRUE;
SDL_bool MousePressed = SDL_FALSE;
Element element_param = SAND; //Par défaut du sable
SDL_bool Pause = SDL_FALSE;
SDL_bool Help = SDL_FALSE;
int Mouse_x = 0;
int Mouse_y = 0;
SDL_Color ColorSand={.r=194, .g=178, .b=128, .a=SDL_ALPHA_OPAQUE};
SDL_Color ColorWater={.r=212, .g=241, .b=249, .a=SDL_ALPHA_OPAQUE};
SDL_Color Blanc={.r=255, .g=255, .b=255, .a=SDL_ALPHA_OPAQUE};
SDL_Color ColorConcrete={.r=168, .g=167, .b=164, .a=SDL_ALPHA_OPAQUE};
SDL_Color ColorWood={.r=68, .g=48, .b=34, .a=SDL_ALPHA_OPAQUE};
SDL_Color ColorFire={.r=252, .g=100, .b=0, .a=SDL_ALPHA_OPAQUE};
SDL_Color ColorSmoke={.r=115, .g=130, .b=118, .a=SDL_ALPHA_OPAQUE};
SDL_Color Blanc_casse;

void Init(SDL_Window** fenetre, SDL_Renderer** renderer)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        ExitWithError("Erreur d'initialisation de SDL");
    }
    printf("SDL initialized successfully !\n");
    
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("version : %d.%d.%d\n",nb.major,nb.minor,nb.patch);

    *(fenetre) = SDL_CreateWindow("Cellular Automata", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
                              //Titre, point x, point y, Largeur, hauteur, options (ici 0 = default)
    if(*(fenetre) == NULL)
    {
        ExitWithError("Erreur d'initialisation de la fenêtre");
    }
    
    *(renderer) = SDL_CreateRenderer(*(fenetre), -1, SDL_RENDERER_SOFTWARE);
    if(*(renderer) == NULL)
    {
        ExitWithError("Erreur d'initialisation du renderer");
    }
    //Allocation mémoire pour la grille 110x160
    grille = malloc(sizeof(pixel*) * GRID_HEIGHT); 
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        grille[i] = malloc(sizeof(pixel)*GRID_WIDTH);
    }    
}

void ExitWithError(const char* message)
{
    SDL_Log("Erreur : %s -> %s", message, SDL_GetError());
    exit(EXIT_FAILURE);
}

void FrameCap(Uint32 starting_tick,int fps)
{
    if ((1000/fps) > SDL_GetTicks() - starting_tick)
    {
        SDL_Delay(1000/fps - (SDL_GetTicks()-starting_tick));
    }
}

void ClearGrid(pixel** grille)
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            grille[y][x].ID = PARTICULE_MAX + 1;
            grille[y][x].element = VOID;
        }
    }
}