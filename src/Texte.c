#include "Texte.h"
TTF_Font* Sans=NULL;

struct MsgHelp
{
    SDL_Surface* MessageHelp_MainSurface;
    SDL_Texture* MessageHelp_Texture;
    SDL_Rect MessageHelp_RectTexture;
}MessageHelpStruct;


void InitTexte()
{
    if(TTF_Init() != 0){ExitWithError("TTF_Init");};
    Sans = TTF_OpenFont(ARIAL,24);
    if(!Sans){printf("%s\n", TTF_GetError());}
}

void UpdateTexteNumberParticules(int current_particule, SDL_Renderer** renderer)
{
    SDL_Texture* MessageNbPart_Texture;
    char MessageNbPart_txt[5];
    SDL_Rect MessageNbPart_Rect = {.h=50, .w=25, .x=0, .y=0};
    
    sprintf(MessageNbPart_txt, "%d", current_particule); //Convert int current_particule into char txt
    int size = 0;
    //Scale the box for the text, probably a better way to do this but my monke brain can't think of anything rn
    if (current_particule < 10)//0..9
        size = 0;
    else if(current_particule < 100)//10..99
        size = 1;
    else if(current_particule < 1000)//100..999
        size = 2;
    else if(current_particule < 10000)//1000..10 000
        size = 3;
    
    MessageNbPart_Rect.w = 25 + (25*size);
    
    SDL_Surface* MessageNbPart_Surface;
    MessageNbPart_Surface = TTF_RenderText_Solid(Sans, MessageNbPart_txt, Blanc);
    if(MessageNbPart_Surface == NULL){ExitWithError("TTF_RenderText_Solid");}
    MessageNbPart_Texture = SDL_CreateTextureFromSurface(*renderer, MessageNbPart_Surface);
    if(MessageNbPart_Texture == NULL){ExitWithError("SDL_CreateTextureFromSurface");}
    if(SDL_RenderCopy(*renderer, MessageNbPart_Texture, NULL, &MessageNbPart_Rect) != 0){ExitWithError("SDL_RenderCopy");}
    SDL_FreeSurface(MessageNbPart_Surface);
    SDL_DestroyTexture(MessageNbPart_Texture);
}

void PrintPause(SDL_Renderer** renderer)
{
    const char* MessagePause_txt = "Pause";
    SDL_Surface* MessagePause_Surface;
    SDL_Texture* MessagePause_Texture;
    SDL_Rect MessagePause_Rect = {.h=50, .w=125, .x=0, .y=50};
    MessagePause_Surface = TTF_RenderText_Solid(Sans, MessagePause_txt, Blanc);
    if(MessagePause_Surface == NULL){ExitWithError("TTF_RenderText_Solid");}
    MessagePause_Texture = SDL_CreateTextureFromSurface(*renderer, MessagePause_Surface);
    if(MessagePause_Texture == NULL){ExitWithError("SDL_CreateTextureFromSurface");}
    if(SDL_RenderCopy(*renderer, MessagePause_Texture, NULL, &MessagePause_Rect) != 0){ExitWithError("SDL_RenderCopy");}
    SDL_FreeSurface(MessagePause_Surface);
    SDL_DestroyTexture(MessagePause_Texture);
}

void PrintFrameByFrameMode(SDL_Renderer** renderer)
{
    const char* MessageFrameByFrame_txt = "Frame by Frame";
    SDL_Surface* MessageFrameByFrame_Surface;
    SDL_Texture* MessageFrameByFrame_Texture;
    SDL_Rect MessageFrameByFrame_Rect = {.h=50, .w=200, .x=0, .y=50};
    MessageFrameByFrame_Surface = TTF_RenderText_Solid(Sans, MessageFrameByFrame_txt, Blanc);
    if(MessageFrameByFrame_Surface == NULL){ExitWithError("TTF_RenderText_Solid");}
    MessageFrameByFrame_Texture = SDL_CreateTextureFromSurface(*renderer, MessageFrameByFrame_Surface);
    if(MessageFrameByFrame_Texture == NULL){ExitWithError("SDL_CreateTextureFromSurface");}
    if(SDL_RenderCopy(*renderer, MessageFrameByFrame_Texture, NULL, &MessageFrameByFrame_Rect) != 0){ExitWithError("SDL_RenderCopy");}
    SDL_FreeSurface(MessageFrameByFrame_Surface);
    SDL_DestroyTexture(MessageFrameByFrame_Texture);
}

void PrintAddOrDeleteMode(SDL_Renderer** renderer)
{
    const char* MessageAddOrDelete_txt;
    const char* MessageElement_txt;
    if(ParticuleToBeDestroyed)
        MessageAddOrDelete_txt = "Delete";
    else if(!ParticuleToBeDestroyed)
        MessageAddOrDelete_txt = "Add";
    switch (element_param)
    {
    case SAND:
        MessageElement_txt = "Sand";
        break;
    case LIQUID:
        MessageElement_txt = "Water";
        break;
    case SOLID:
        MessageElement_txt = "Concrete";
        break;
    case WOOD:
        MessageElement_txt = "Wood";
        break;
    case FIRE:
        MessageElement_txt = "Fire";
        break;
    default:
        break;
    }
    SDL_Surface* MessageAddOrDelete_Surface;
    SDL_Surface* MessageElement_Surface;
    SDL_Texture* MessageAddOrDelete_Texture;
    SDL_Texture* MessageElement_Texture;
    SDL_Rect MessageAddOrDelete_Rect = {.h=50, .w=100, .x=130, .y=0};
    SDL_Rect MessageElement_Rect = {.h=50, .w=100, .x=250, .y=0};
    MessageElement_Surface = TTF_RenderText_Solid(Sans, MessageElement_txt, Blanc);
    if(MessageElement_Surface == NULL){ExitWithError("TTF_RenderText_Solid");}
    MessageAddOrDelete_Surface = TTF_RenderText_Solid(Sans, MessageAddOrDelete_txt, Blanc);
    if(MessageAddOrDelete_Surface == NULL){ExitWithError("TTF_RenderText_Solid");}
    MessageElement_Texture = SDL_CreateTextureFromSurface(*renderer, MessageElement_Surface);
    if(MessageElement_Texture == NULL){ExitWithError("SDL_CreateTextureFromSurface");}
    MessageAddOrDelete_Texture = SDL_CreateTextureFromSurface(*renderer, MessageAddOrDelete_Surface);
    if(MessageAddOrDelete_Texture == NULL){ExitWithError("SDL_CreateTextureFromSurface");}
    if(SDL_RenderCopy(*renderer, MessageAddOrDelete_Texture, NULL, &MessageAddOrDelete_Rect) != 0){ExitWithError("SDL_RenderCopy");}
    if(!ParticuleToBeDestroyed)
        if(SDL_RenderCopy(*renderer, MessageElement_Texture, NULL, &MessageElement_Rect) != 0){ExitWithError("SDL_RenderCopy");}
    SDL_FreeSurface(MessageElement_Surface);
    SDL_FreeSurface(MessageAddOrDelete_Surface);
    SDL_DestroyTexture(MessageElement_Texture);
    SDL_DestroyTexture(MessageAddOrDelete_Texture);
}

void HelpMenuLoadUnload(int state)
{
    if(state==LOAD)//Load
    {
        SDL_Surface** MessageHelp_Surfaces;
        SDL_Rect MessageHelp_RectTexture_Test = {.x=100, .y=100, .h=400, .w=600};
        Uint32 rmask, gmask, bmask, amask;
        SDL_Rect MessageHelp_RectColorSurface = {.x=0, .y=0, .w=700, .h=400};
        #if SDL_BYTEORDER == SDL_BIGENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x00000000;
        #else
            rmask = 0x0000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0x00000000;
        #endif
        MessageHelpStruct.MessageHelp_RectTexture = MessageHelp_RectTexture_Test;
        const char* Messages[] = {
            "x : Switch between the add or delete mode",
            "f : Frame by frame mode, -> to move up a frame",
            "1 : Select sand          |  4 : Select wood", //10 spaces
            "2 : Select water         |  5 : Select fire",
            "3 : Select concrete",
            "Space : Pause",
            "F1 : Display this help",
            "OK"
        };
        SDL_Rect MessageHelp_Rect[] = {
            {.x=0, .y=0,   .h=50, .w=200},
            {.x=0, .y=50,  .h=50, .w=200},
            {.x=0, .y=100, .h=50, .w=100},
            {.x=0, .y=150, .h=50, .w=100},
            {.x=0, .y=200, .h=50, .w=100},
            {.x=0, .y=250, .h=50, .w=100},
            {.x=0, .y=300, .h=50, .w=100},
            {.x=0, .y=350, .h=50, .w=50}
        };
        size_t MessageTotal = sizeof(Messages)/sizeof(Messages[0]); //Calculates the number of items in Messages array
        //Load the surface with the needed text
        MessageHelp_Surfaces = malloc(sizeof(SDL_Surface*)*MessageTotal); //I need to use malloc more, so am not bad with it
        for (int i = 0; i < MessageTotal; i++)
        {
            MessageHelp_Surfaces[i] = TTF_RenderText_Solid(Sans, Messages[i], Blanc);
        }
        MessageHelpStruct.MessageHelp_MainSurface = SDL_CreateRGBSurface(0,700,400,32,rmask,gmask,bmask,amask); //Create the main surface
        if(MessageHelpStruct.MessageHelp_MainSurface == NULL){ExitWithError("SDL_CreateRGBSurface");}
        //Make the main surface red
        SDL_FillRect(MessageHelpStruct.MessageHelp_MainSurface, &MessageHelp_RectColorSurface, SDL_MapRGB(MessageHelpStruct.MessageHelp_MainSurface->format, 255, 0,0));
        for (int i = 0; i < MessageTotal; i++)//Add the text to the main surface
        {
            if(SDL_BlitSurface(MessageHelp_Surfaces[i], NULL, MessageHelpStruct.MessageHelp_MainSurface, &MessageHelp_Rect[i]) != 0){ExitWithError("SDL_BlitSurface");}    
        }
        //free memory
        for (int i = 0; i < MessageTotal; i++)
        {
            SDL_FreeSurface(MessageHelp_Surfaces[i]);
        }
        free(MessageHelp_Surfaces);
        MessageHelp_Surfaces = NULL;
    }
    else if(state==UNLOAD)//Unload
    {
        SDL_FreeSurface(MessageHelpStruct.MessageHelp_MainSurface);
    }
}

void PrintHelpMenu(SDL_Renderer** renderer)
{
    //!CPU intensive function, making texture from a large surface is a bad idea, will have to be replaced
    MessageHelpStruct.MessageHelp_Texture = SDL_CreateTextureFromSurface(*renderer, MessageHelpStruct.MessageHelp_MainSurface);//Convert the surface to a texture
    if(SDL_RenderCopy(*renderer, MessageHelpStruct.MessageHelp_Texture, NULL, &MessageHelpStruct.MessageHelp_RectTexture) != 0){ExitWithError("SDL_RenderCopy");}
    SDL_DestroyTexture(MessageHelpStruct.MessageHelp_Texture);
}