#include "Update.h"

void UpdateParticule(int x, int y, pixel** grille, Particule Particules[PARTICULE_MAX])
{
    switch (grille[y][x].element)
    {
    case SAND:
        if((grille[y+1][x].element == VOID) || (grille[y+1][x].element == LIQUID))//Si la place en bas est libre
        {
            int id_part = grille[y][x].ID;
            if(Particules[id_part].hasbeenupdated == SDL_FALSE) //On update sa pos
            {
                if(grille[y+1][x].element == LIQUID) //Si la place en bas est du liquide, on déplace le liquide
                {
                    int id_neighbour = grille[y+1][x].ID; //ID de l'eau
                    if(Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                    {
                        Particules[id_part].pos_y_norm += 1;
                        Particules[id_part].box.y += PARTICULE_SIZE;
                        Particules[id_part].hasbeenupdated = SDL_TRUE;
                        Particules[id_neighbour].pos_y_norm -=1;
                        Particules[id_neighbour].box.y -=PARTICULE_SIZE;
                        Particules[id_neighbour].hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = LIQUID;
                        grille[y][x].ID = Particules[id_neighbour].ID;
                        grille[y+1][x].element = SAND;
                        grille[y+1][x].ID = Particules[id_part].ID;
                    }
                }
                else
                {
                    Particules[id_part].pos_y_norm += 1;
                    Particules[id_part].box.y += PARTICULE_SIZE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].ID = PARTICULE_MAX + 1;
                    grille[y+1][x].element = SAND;
                    grille[y+1][x].ID = Particules[id_part].ID;
                }
            }
            break;
        } 
        if(x-1>=0)//Check if index of array will exist, en bas à gauche
        {
            if(((grille[y+1][x-1].element == VOID) || (grille[y+1][x-1].element == LIQUID)))//Sinon si la place en bas à gauche est libre
            {
                int id_part=grille[y][x].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE)//On update sa pos
                {
                    if(grille[y+1][x-1].element == LIQUID)
                    {
                        int id_neighbour = grille[y+1][x-1].ID;
                        if(Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                        {
                            int c = 0;
                            while (grille[y+1-c][x-1].element != VOID)
                            {
                                c++;
                            }
                            Particules[id_neighbour].pos_y_norm -= c;
                            Particules[id_neighbour].box.y -= PARTICULE_SIZE*c;
                            Particules[id_neighbour].hasbeenupdated = SDL_TRUE;
                            Particules[id_part].pos_y_norm += 1; 
                            Particules[id_part].pos_x_norm -= 1; 
                            Particules[id_part].box.x -= PARTICULE_SIZE; 
                            Particules[id_part].box.y += PARTICULE_SIZE;
                            Particules[id_part].hasbeenupdated = SDL_TRUE;
                            grille[y+1][x-1].element = SAND;
                            grille[y+1][x-1].ID = id_part;
                            grille[y][x].element = VOID;
                            grille[y][x].ID = PARTICULE_MAX + 1;  
                            grille[y+1-c][x-1].element = LIQUID;
                            grille[y+1-c][x-1].ID = id_neighbour;
                        }
                    }
                    else
                    {
                        Particules[id_part].pos_y_norm += 1;
                        Particules[id_part].pos_x_norm -= 1;
                        Particules[id_part].box.y+=PARTICULE_SIZE;
                        Particules[id_part].box.x-=PARTICULE_SIZE;
                        Particules[id_part].hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].ID = PARTICULE_MAX + 1;
                        grille[y+1][x-1].element = SAND;
                        grille[y+1][x-1].ID = id_part;
                    } 
                }
                break;
            }
        }
        if(x+1<GRID_WIDTH)//Check if index of array will exist, en bas à droite
        {
            if(((grille[y+1][x+1].element == VOID) || (grille[y+1][x+1].element == LIQUID)))//Sinon si la place en bas à droite est libre 
            {
                int id_part = grille[y][x].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE)
                {
                    if(grille[y+1][x+1].element == LIQUID)
                    {
                        int id_neighbour = grille[y+1][x+1].ID;
                        if(Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                        {
                            int c = 0;
                            while (grille[y+1-c][x+1].element != VOID)
                            {
                                c++;
                            }
                            Particules[id_neighbour].pos_y_norm -= c;
                            Particules[id_neighbour].box.y -= PARTICULE_SIZE*c;
                            Particules[id_neighbour].hasbeenupdated = SDL_TRUE;
                            Particules[id_part].pos_y_norm += 1; 
                            Particules[id_part].pos_x_norm += 1; 
                            Particules[id_part].box.x += PARTICULE_SIZE; 
                            Particules[id_part].box.y += PARTICULE_SIZE;
                            Particules[id_part].hasbeenupdated = SDL_TRUE;
                            grille[y+1][x+1].element = SAND;
                            grille[y+1][x+1].ID = id_part;
                            grille[y][x].element = VOID;
                            grille[y][x].ID = PARTICULE_MAX+1;
                            grille[y+1-c][x+1].element = LIQUID;
                            grille[y+1-c][x+1].ID = id_neighbour;
                        }
                    }
                    else 
                    {
                        Particules[id_part].pos_y_norm += 1;
                        Particules[id_part].pos_x_norm += 1;
                        Particules[id_part].box.y += PARTICULE_SIZE;
                        Particules[id_part].box.x += PARTICULE_SIZE;
                        Particules[id_part].hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].ID = PARTICULE_MAX + 1;
                        grille[y+1][x+1].element = SAND;
                        grille[y+1][x+1].ID = id_part;
                    }
                }
                break;
            }
        }
        break;
        
    case LIQUID:
        if(grille[y+1][x].element == VOID)//Si la place en bas est libre
        {
            int id_part = grille[y][x].ID;
            if(Particules[id_part].hasbeenupdated == SDL_FALSE) //On update sa pos
            {
                Particules[id_part].pos_y_norm += 1;
                Particules[id_part].box.y += PARTICULE_SIZE;
                Particules[id_part].hasbeenupdated = SDL_TRUE;
                grille[y][x].element = VOID;
                grille[y][x].ID = PARTICULE_MAX + 1;
                grille[y+1][x].element = LIQUID;
                grille[y+1][x].ID = id_part;
            }
            break;
        }
        if (x-1 >=0)
        {
            if(grille[y+1][x-1].element == VOID)//Sinon si la place en bas à gauche est libre
            {
                int id_part = grille[y][x].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE)//On update sa pos
                {
                    Particules[id_part].pos_y_norm += 1;
                    Particules[id_part].pos_x_norm -= 1;
                    Particules[id_part].box.y+=PARTICULE_SIZE;
                    Particules[id_part].box.x-=PARTICULE_SIZE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].ID = PARTICULE_MAX + 1;
                    grille[y+1][x-1].element = LIQUID;
                    grille[y+1][x-1].ID = id_part;
                }
                break;
            }
        }
        if (x+1<GRID_WIDTH)
        {
            if(grille[y+1][x+1].element == VOID)//Sinon si la place en bas à droite est libre 
            {
                int id_part = grille[y][x].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE)
                {
                    Particules[id_part].pos_y_norm += 1;
                    Particules[id_part].pos_x_norm += 1;
                    Particules[id_part].box.y+=PARTICULE_SIZE;
                    Particules[id_part].box.x+=PARTICULE_SIZE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].ID = PARTICULE_MAX + 1;
                    grille[y+1][x+1].element = LIQUID;
                    grille[y+1][x+1].ID = id_part; 
                }
                break;
            }
            if((grille[y][x+1].element == VOID) && (rand()%2 == 0))//On glisse ou à droite...
            {
                int id_part = grille[y][x].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE)
                {
                    Particules[id_part].pos_x_norm += 1;
                    Particules[id_part].box.x+=PARTICULE_SIZE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].ID = PARTICULE_MAX + 1;
                    grille[y][x+1].element = LIQUID;
                    grille[y][x+1].ID = id_part;
                }
                break;
            }
        }
        if (x-1>=0)
        {
            if((grille[y][x-1].element == VOID) && ((x-1) >= 0))//Ou à gauche
            {
                int id_part = grille[y][x].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE)
                {
                    Particules[id_part].pos_x_norm -= 1;
                    Particules[id_part].box.x-=PARTICULE_SIZE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].ID = PARTICULE_MAX + 1;
                    grille[y][x-1].element = LIQUID;
                    grille[y][x-1].ID = id_part;
                }
                break;
            }
        }    
        break;
    case FIRE:
    {
        int id_part = grille[y][x].ID;
        Particules[id_part].update_counter++;
        if (grille[y+1][x].element == LIQUID) //Voisin du bas
        {
            int id_neighbour = grille[y+1][x].ID;
            if(Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
            {
                Particules[id_part].element = SMOKE;
                Particules[id_part].hasbeenupdated = SDL_TRUE;
                Particules[id_part].update_counter = 0;

                if(Particules[current_particule-1].element != VOID)
                {
                    Particules[id_neighbour] = Particules[current_particule-1];
                    Particules[id_neighbour].ID = id_neighbour;
                    grille[Particules[id_neighbour].pos_y_norm][Particules[id_neighbour].pos_x_norm].ID = id_neighbour;
                }
                current_particule--;
                
                Particules[id_neighbour].hasbeenupdated = SDL_TRUE;

                grille[y][x].element = SMOKE;
                grille[y+1][x].element = VOID;
                grille[y+1][x].ID = PARTICULE_MAX+1;
            }
        }
        if ((y-1)>=0 && Particules[id_part].hasbeenupdated == SDL_FALSE) //Voisin du haut, on check dabord si on peut regarder la mémoire, pas élégant, à fix
        {
            if(grille[y-1][x].element == LIQUID) //Voisin du haut
            {
                int id_neighbour = grille[y-1][x].ID;
                if(Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                {
                    Particules[id_part].element = SMOKE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                    Particules[id_part].update_counter = 0;

                    if(Particules[current_particule-1].element != VOID)
                    {
                        Particules[id_neighbour] = Particules[current_particule-1];
                        Particules[id_neighbour].ID = id_neighbour;
                        grille[Particules[id_neighbour].pos_y_norm][Particules[id_neighbour].pos_x_norm].ID = id_neighbour;
                    }
                    current_particule--;
                    Particules[id_neighbour].hasbeenupdated = SDL_TRUE;

                    grille[y][x].element = SMOKE;
                    grille[y-1][x].element = VOID;
                    grille[y-1][x].ID = PARTICULE_MAX+1;
                }
            }
        }
        if (x+1<GRID_WIDTH && Particules[id_part].hasbeenupdated == SDL_FALSE)
        {
            if(grille[y][x+1].element == LIQUID) //Voisin de droite
            {
                int id_neighbour = grille[y][x+1].ID;
                if(Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                {
                    Particules[id_part].element = SMOKE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                    Particules[id_part].update_counter = 0;

                    if(Particules[current_particule-1].element != VOID)
                    {
                        Particules[id_neighbour] = Particules[current_particule-1];
                        Particules[id_neighbour].ID = id_neighbour;
                        grille[Particules[id_neighbour].pos_y_norm][Particules[id_neighbour].pos_x_norm].ID = id_neighbour;
                    }
                    current_particule--;
                    Particules[id_neighbour].hasbeenupdated = SDL_TRUE;

                    grille[y][x].element = SMOKE;
                    grille[y][x+1].element = VOID;
                    grille[y][x+1].ID = PARTICULE_MAX+1;
                }
            }
        }
        if (x-1>=0 && Particules[id_part].hasbeenupdated == SDL_FALSE)
        {
            if (grille[y][x-1].element == LIQUID) //Voisin de gauche
            {
                int id_neighbour = grille[y][x-1].ID;
                if(Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                {
                    Particules[id_part].element = SMOKE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                    Particules[id_part].update_counter = 0;

                    if(Particules[current_particule-1].element != VOID)
                    {
                        Particules[id_neighbour] = Particules[current_particule-1];
                        Particules[id_neighbour].ID = id_neighbour;
                        grille[Particules[id_neighbour].pos_y_norm][Particules[id_neighbour].pos_x_norm].ID = id_neighbour;
                    }
                    current_particule--;
                    Particules[id_neighbour].hasbeenupdated = SDL_TRUE;

                    grille[y][x].element = SMOKE;
                    grille[y][x-1].element = VOID;
                    grille[y][x-1].ID = PARTICULE_MAX+1;
                }
            }
        }

        if(Particules[id_part].update_counter > 50)
        {
            if(grille[y][x+1].element == WOOD)//Droite, si il y a du bois à côté, on met le feu au bois 
            {
                int id_neighbour = grille[y][x+1].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE && Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                {
                    grille[y][x+1].element = FIRE;
                    Particules[id_neighbour].element = FIRE;
                    Particules[id_neighbour].hasbeenupdated = SDL_TRUE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                }
            }
            else if(grille[y][x-1].element == WOOD) //Gauche
            {
                int id_neighbour = grille[y][x-1].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE && Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                {
                    grille[y][x-1].element = FIRE;
                    Particules[id_neighbour].element = FIRE;
                    Particules[id_neighbour].hasbeenupdated = SDL_TRUE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                }
            }
            else if(grille[y+1][x].element == WOOD) //En bas
            {
                int id_neighbour = grille[y+1][x].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE && Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                {
                    grille[y+1][x].element = FIRE;
                    Particules[id_neighbour].element = FIRE;
                    Particules[id_neighbour].hasbeenupdated = SDL_TRUE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                }
            }
            else if(grille[y-1][x].element == WOOD) //En haut
            {
                int id_neighbour = grille[y-1][x].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE && Particules[id_neighbour].hasbeenupdated == SDL_FALSE)
                {
                    grille[y-1][x].element = FIRE;
                    Particules[id_neighbour].element = FIRE;
                    Particules[id_neighbour].hasbeenupdated = SDL_TRUE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                }
            }
        }

        if(Particules[id_part].update_counter > 200)//On se transforme en fumée
        {
            if(Particules[id_part].hasbeenupdated == SDL_FALSE)
            {
                grille[y][x].element = SMOKE;
                Particules[id_part].element = SMOKE;
                Particules[id_part].update_counter = 0;
                Particules[id_part].hasbeenupdated = SDL_TRUE;
            }
        }
        else if(grille[y+1][x].element == VOID) //Sinon on tombe
        {
            if(Particules[id_part].hasbeenupdated == SDL_FALSE)
            {
                Particules[id_part].pos_y_norm += 1;
                Particules[id_part].box.y += PARTICULE_SIZE;
                Particules[id_part].hasbeenupdated = SDL_TRUE;
                grille[y][x].element = VOID;
                grille[y][x].ID = PARTICULE_MAX+1;
                grille[y+1][x].element = FIRE;
                grille[y+1][x].ID = Particules[id_part].ID;
            }
        }
        break;
    }
    case SMOKE:
        if(y-1 >=0)//Si le haut n'a pas été atteint
        {
            if(grille[y-1][x].element == VOID)//Si la place en haut est libre
            {
                int id_part = grille[y][x].ID;
                if(Particules[id_part].hasbeenupdated == SDL_FALSE) //On update sa pos
                {
                    Particules[id_part].pos_y_norm -= 1;
                    Particules[id_part].box.y -= PARTICULE_SIZE;
                    Particules[id_part].hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].ID = PARTICULE_MAX + 1;
                    grille[y-1][x].element = SMOKE;
                    grille[y-1][x].ID = id_part;
                }
                break;
            }
            if(x-1>=0)
            {
                if(grille[y-1][x-1].element == VOID)//Sinon si la place en haut à gauche est libre
                {
                    int id_part = grille[y][x].ID;
                    if(Particules[id_part].hasbeenupdated == SDL_FALSE)//On update sa pos
                    {
                        Particules[id_part].pos_y_norm -= 1;
                        Particules[id_part].pos_x_norm -= 1;
                        Particules[id_part].box.y-=PARTICULE_SIZE;
                        Particules[id_part].box.x-=PARTICULE_SIZE;
                        Particules[id_part].hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].ID = PARTICULE_MAX + 1;
                        grille[y-1][x-1].element = SMOKE;
                        grille[y-1][x-1].ID = id_part;
                    }
                    break;
                }
            }
            if(x+1<GRID_WIDTH)
            {
                if(grille[y-1][x+1].element == VOID)//Sinon si la place en haut à droite est libre 
                {
                    int id_part = grille[y][x].ID;
                    if(Particules[id_part].hasbeenupdated == SDL_FALSE)
                    {
                        Particules[id_part].pos_y_norm -= 1;
                        Particules[id_part].pos_x_norm += 1;
                        Particules[id_part].box.y-=PARTICULE_SIZE;
                        Particules[id_part].box.x+=PARTICULE_SIZE;
                        Particules[id_part].hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].ID = PARTICULE_MAX + 1;
                        grille[y-1][x+1].element = SMOKE;
                        grille[y-1][x+1].ID = id_part; 
                    }
                    break;
                }
                if((grille[y][x+1].element == VOID) && rand()%2 == 0)//On glisse ou à droite...
                {
                    int id_part = grille[y][x].ID;
                    if(Particules[id_part].hasbeenupdated == SDL_FALSE)
                    {
                        Particules[id_part].pos_x_norm += 1;
                        Particules[id_part].box.x+=PARTICULE_SIZE;
                        Particules[id_part].hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].ID = PARTICULE_MAX + 1;
                        grille[y][x+1].element = SMOKE;
                        grille[y][x+1].ID = id_part;
                    }
                    break;
                }
            }
            if(x-1 >= 0)
            {
                if(grille[y][x-1].element == VOID)//Ou à gauche
                {
                    int id_part = grille[y][x].ID;
                    if(Particules[id_part].hasbeenupdated == SDL_FALSE)
                    {
                        Particules[id_part].pos_x_norm -= 1;
                        Particules[id_part].box.x -= PARTICULE_SIZE;
                        Particules[id_part].hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].ID = PARTICULE_MAX + 1;
                        grille[y][x-1].element = SMOKE;
                        grille[y][x-1].ID = id_part;
                    }
                    break;
                }
            }
        }
        else //Sinon on a atteint le haut 
        {
            if(x+1<GRID_WIDTH)
            {
                if((grille[y][x+1].element == VOID) && rand()%2 == 0)//On glisse ou à droite...
                {
                    int id_part = grille[y][x].ID;
                    if(Particules[id_part].hasbeenupdated == SDL_FALSE)
                    {
                        Particules[id_part].pos_x_norm += 1;
                        Particules[id_part].box.x+=PARTICULE_SIZE;
                        Particules[id_part].hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].ID = PARTICULE_MAX + 1;
                        grille[y][x+1].element = SMOKE;
                        grille[y][x+1].ID = id_part;
                    }
                    break;
                }
            }
            if(x-1>=0)
            {
                if((grille[y][x-1].element == VOID) && ((x-1) >= 0))//Ou à gauche
                {
                    int id_part = grille[y][x].ID;
                    if(Particules[id_part].hasbeenupdated == SDL_FALSE)
                    {
                        Particules[id_part].pos_x_norm -= 1;
                        Particules[id_part].box.x -= PARTICULE_SIZE;
                        Particules[id_part].hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].ID = PARTICULE_MAX + 1;
                        grille[y][x-1].element = SMOKE;
                        grille[y][x-1].ID = id_part;
                    }
                    break;
                }
            }
        }
    break;
    default:
        break;
    }
}

void UpdateParticulesNumber(Mode mode, pixel** grille, Particule Particules[PARTICULE_MAX], Element element_param)
{
    switch (mode)
    {
    case AUTO:
        if((frame_count == 10) && (current_particule < PARTICULE_MAX)) //Rajoute une particule toute les 10 frames
        {
            Particules[current_particule].element = SAND;
            Particules[current_particule].hasbeenupdated = SDL_FALSE;
            Particules[current_particule].box.w = PARTICULE_SIZE;
            Particules[current_particule].box.h = PARTICULE_SIZE;
            Particules[current_particule].box.x = 400;//(rand()%159)*5;
            Particules[current_particule].box.y = 50;
            Particules[current_particule].pos_x_norm = Particules[current_particule].box.x/5;
            Particules[current_particule].pos_y_norm = Particules[current_particule].box.y/5;
            grille[Particules[current_particule].pos_y_norm][Particules[current_particule].pos_x_norm].element = Particules[current_particule].element;
            grille[Particules[current_particule].pos_y_norm][Particules[current_particule].pos_x_norm].ID = Particules[current_particule].ID;
            current_particule++;
            frame_count = 0;
        }
        break;
    case MANUEL:
        if((ParticuleToBeCreated) && (!ParticuleToBeDestroyed) && (frame_count > 3 || FrameByFrameMode)) //Rajoute une particule tous les clicks
        {
            int Mouse_x, Mouse_y;
            SDL_GetMouseState(&Mouse_x, &Mouse_y);
            if(Mouse_x%PARTICULE_SIZE != 0)
            {
                if(Mouse_x%PARTICULE_SIZE>=3){Mouse_x += (PARTICULE_SIZE-Mouse_x%PARTICULE_SIZE);}
                else{Mouse_x -= Mouse_x%PARTICULE_SIZE;}
            }
            if(Mouse_y%PARTICULE_SIZE != 0)
            {
                if(Mouse_y%PARTICULE_SIZE>=3){Mouse_y += (PARTICULE_SIZE-Mouse_y%PARTICULE_SIZE);}
                else{Mouse_y -= Mouse_y%PARTICULE_SIZE;}
            }
            for (int i = 0; i <= TO_PARTCULE_SIZE(cursor_pad); i++)
            {
                for (int y = 0; y <= TO_PARTCULE_SIZE(cursor_pad); y++)
                {
                    if(TO_PARTCULE_SIZE(Mouse_y)+y < GRID_HEIGHT && TO_PARTCULE_SIZE(Mouse_x)+i < GRID_WIDTH && grille[TO_PARTCULE_SIZE(Mouse_y)+y][TO_PARTCULE_SIZE(Mouse_x)+i].element == VOID  && (current_particule < PARTICULE_MAX)) //On check que l'emplacement est bien vide
                    {
                        Particules[current_particule].ID = current_particule;
                        Particules[current_particule].element = element_param;
                        Particules[current_particule].hasbeenupdated = SDL_TRUE;
                        Particules[current_particule].box.w = PARTICULE_SIZE;
                        Particules[current_particule].box.h = PARTICULE_SIZE;
                        Particules[current_particule].box.x = Mouse_x+TO_PIXEL_SIZE(i);
                        Particules[current_particule].box.y = Mouse_y+TO_PIXEL_SIZE(y);
                        Particules[current_particule].pos_x_norm = TO_PARTCULE_SIZE(Particules[current_particule].box.x);
                        Particules[current_particule].pos_y_norm = TO_PARTCULE_SIZE(Particules[current_particule].box.y);
                        grille[Particules[current_particule].pos_y_norm][Particules[current_particule].pos_x_norm].element = Particules[current_particule].element;
                        grille[Particules[current_particule].pos_y_norm][Particules[current_particule].pos_x_norm].ID = Particules[current_particule].ID;
                        current_particule++;
                        frame_count = 0;
                    }
                }
            }
        }
        else if(ParticuleToBeDestroyed && ParticuleToBeCreated && (frame_count > 3 || FrameByFrameMode)) //Delete a particule
        {
            int Mouse_x, Mouse_y;
            SDL_GetMouseState(&Mouse_x, &Mouse_y);
            if(Mouse_x%PARTICULE_SIZE != 0)
            {
                if(Mouse_x%PARTICULE_SIZE>=3){Mouse_x += (PARTICULE_SIZE-Mouse_x%PARTICULE_SIZE);}
                else{Mouse_x -= Mouse_x%PARTICULE_SIZE;}
            }
            if(Mouse_y%PARTICULE_SIZE != 0)
            {
                if(Mouse_y%PARTICULE_SIZE>=3){Mouse_y += (PARTICULE_SIZE-Mouse_y%PARTICULE_SIZE);}
                else{Mouse_y -= Mouse_y%PARTICULE_SIZE;}
            }
            if(TO_PARTCULE_SIZE(Mouse_y) < GRID_HEIGHT && TO_PARTCULE_SIZE(Mouse_x) < GRID_WIDTH && grille[TO_PARTCULE_SIZE(Mouse_y)][TO_PARTCULE_SIZE(Mouse_x)].element != VOID && grille[Mouse_y/5][Mouse_x/5].element != FLOOR)
            {
                int id_part = grille[TO_PARTCULE_SIZE(Mouse_y)][TO_PARTCULE_SIZE(Mouse_x)].ID;
                grille[TO_PARTCULE_SIZE(Mouse_y)][TO_PARTCULE_SIZE(Mouse_x)].element = VOID;
                grille[TO_PARTCULE_SIZE(Mouse_y)][TO_PARTCULE_SIZE(Mouse_x)].ID = PARTICULE_MAX + 1;
                //Replace with the last particule in the list
                if(Particules[current_particule-1].element != VOID)
                {
                    Particules[id_part] = Particules[current_particule-1]; //Replace all parameters
                    Particules[id_part].ID = id_part; //change the ID
                    grille[Particules[id_part].pos_y_norm][Particules[id_part].pos_x_norm].ID = id_part; //Change the grid ID
                }
                current_particule--;
                frame_count = 0;
            }
        }
        break;
    default:
        break;
    }
    
}

void DrawWaterSelection(int x, int y, SDL_Rect WaterSelection[SELECTION_SIZE*SELECTION_SIZE])
{
    int widths[] = {7,7,2,2};
    int heights[] = {2,2,4,4};
    int xs[4] = {x, x, x, (x+5)} ;
    int ys[4] = {y, (y+4), (y+2), (y+2)};

    for(int i = 0; i<4; i++)
    {
        WaterSelection[i].h = heights[i]*5;
        WaterSelection[i].w = widths[i]*5;
        WaterSelection[i].x = xs[i]*5;
        WaterSelection[i].y = ys[i]*5;
    }
}

void CreateFloor(pixel** grille, SDL_Rect FloorAndWall[GRID_WIDTH+GRID_HEIGHT])
{
    for(int i = 0; i<GRID_WIDTH; i++)
    {
        grille[GRID_HEIGHT-1][i].element = FLOOR;
        grille[GRID_HEIGHT-1][i].ID = PARTICULE_MAX+1;
        FloorAndWall[i].h = PARTICULE_SIZE;
        FloorAndWall[i].w = PARTICULE_SIZE;
        FloorAndWall[i].y = TO_PIXEL_SIZE((GRID_HEIGHT-1));
        FloorAndWall[i].x = TO_PIXEL_SIZE(i);
    }
    for (int i = 0; i<(GRID_HEIGHT-1); i++)
    {
        grille[GRID_HEIGHT-2-i][GRID_WIDTH-1].element = FLOOR;
        grille[GRID_HEIGHT-2-i][GRID_WIDTH-1].ID = PARTICULE_MAX+1;
        FloorAndWall[GRID_WIDTH+i].h = PARTICULE_SIZE;
        FloorAndWall[GRID_WIDTH+i].w = PARTICULE_SIZE;
        FloorAndWall[GRID_WIDTH+i].y = TO_PIXEL_SIZE((GRID_HEIGHT-2-i));
        FloorAndWall[GRID_WIDTH+i].x = TO_PIXEL_SIZE((GRID_WIDTH-1));
    }
}
/*
void DeleteParticule(pixel** grille, int id)
{
    if(Particules[current_particule-1].element != VOID)
    {
        Particules[id] = Particules[current_particule-1]; //Replace all parameters
        Particules[id].ID = id; //change the ID
        grille[Particules[id].pos_y_norm][Particules[id].pos_x_norm].ID = id; //Change the grid ID
        current_particule--;
    }
    
}*/

void UpdateCursor(SDL_Renderer** renderer)
{
    int Mouse_x, Mouse_y;
    SDL_GetMouseState(&Mouse_x, &Mouse_y);
    SDL_Rect Cursor[4];
    Cursor[0].w = Cursor[1].w = Cursor[2].h = Cursor[3].h =  (PARTICULE_SIZE+cursor_pad)+4;
    Cursor[0].h = Cursor[1].h = Cursor[2].w = Cursor[3].w = 1;
    //Set up the cursor
    if(Mouse_x%PARTICULE_SIZE != 0)
    {
        if(Mouse_x%PARTICULE_SIZE>=3){Mouse_x += (PARTICULE_SIZE-Mouse_x%PARTICULE_SIZE);}
        else{Mouse_x -= Mouse_x%PARTICULE_SIZE;}
    }
    if(Mouse_y%PARTICULE_SIZE != 0)
    {
        if(Mouse_y%PARTICULE_SIZE>=3){Mouse_y += (PARTICULE_SIZE-Mouse_y%PARTICULE_SIZE);}
        else{Mouse_y -= Mouse_y%PARTICULE_SIZE;}
    }
    if(TO_PARTCULE_SIZE(Mouse_y) < GRID_HEIGHT && TO_PARTCULE_SIZE(Mouse_x) < GRID_WIDTH)//Mouse is within the grid
    {
        Cursor[0].x = Mouse_x-2;
        Cursor[0].y = Mouse_y-1;
        Cursor[1].x = Mouse_x-2;
        Cursor[1].y = Mouse_y+(PARTICULE_SIZE+cursor_pad);
        Cursor[2].x = Mouse_x-1;
        Cursor[2].y = Mouse_y-2;
        Cursor[3].x = Mouse_x+(PARTICULE_SIZE+cursor_pad);
        Cursor[3].y = Mouse_y-2;
    }
    if(SDL_SetRenderDrawColor(*renderer, Blanc.r ,Blanc.g, Blanc.b, Blanc.a)!=0){ExitWithError("SDL_SetRenderDrawColor");}
    for(int i = 0; i<4; i++)
    {
        if(SDL_RenderFillRect(*renderer, &Cursor[i])!=0){ExitWithError("SDL_RenderFillRect");}
    }
}