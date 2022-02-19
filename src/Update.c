#include "Update.h"

void UpdateParticule(int x, int y, Particule* part_to_update)
{
    switch (part_to_update->element)
    {
    case SAND://! TODO_REWORK : WATER INTERACTION PHYSICS
        if((grille[y+1][x].element == VOID) || (grille[y+1][x].element == LIQUID))//Si la place en bas est libre
        {   
            if(part_to_update->hasbeenupdated == SDL_FALSE) //On update sa pos
            {
                if(grille[y+1][x].element == LIQUID) //Si la place en bas est du liquide, on déplace le liquide
                {
                    Particule* part_neighbour = grille[y+1][x].part;
                    if(part_neighbour->hasbeenupdated == SDL_FALSE)
                    {
                        part_to_update->pos_y_norm += 1;
                        part_to_update->box.y += PARTICULE_SIZE;
                        part_to_update->hasbeenupdated = SDL_TRUE;
                        part_neighbour->pos_y_norm -=1;
                        part_neighbour->box.y -= PARTICULE_SIZE;
                        part_neighbour->hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = LIQUID;
                        grille[y][x].part = part_neighbour;
                        grille[y+1][x].element = SAND;
                        grille[y+1][x].part = part_to_update;
                    }
                }
                else
                {
                    part_to_update->pos_y_norm += 1;
                    part_to_update->box.y += PARTICULE_SIZE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].part = NULL;
                    grille[y+1][x].element = SAND;
                    grille[y+1][x].part = part_to_update;
                }
            }
            break;
        } 
        if(x-1>=0)//Check if index of array will exist, en bas à gauche
        {
            if(((grille[y+1][x-1].element == VOID) || (grille[y+1][x-1].element == LIQUID)))//Sinon si la place en bas à gauche est libre
            {
                if(part_to_update->hasbeenupdated == SDL_FALSE)//On update sa pos
                {
                    if(grille[y+1][x-1].element == LIQUID)
                    {
                        Particule* part_neighbour = grille[y+1][x-1].part;
                        if(part_neighbour->hasbeenupdated == SDL_FALSE)
                        {
                            int c = 0;
                            while (grille[y+1-c][x-1].element != VOID)
                            {
                                c++;
                            }
                            part_neighbour->pos_y_norm -= c;
                            part_neighbour->box.y -= PARTICULE_SIZE*c;
                            part_neighbour->hasbeenupdated = SDL_TRUE;
                            part_to_update->pos_y_norm += 1; 
                            part_to_update->pos_x_norm -= 1; 
                            part_to_update->box.x -= PARTICULE_SIZE; 
                            part_to_update->box.y += PARTICULE_SIZE;
                            part_to_update->hasbeenupdated = SDL_TRUE;
                            grille[y+1][x-1].element = SAND;
                            grille[y+1][x-1].part = part_to_update;
                            grille[y][x].element = VOID;
                            grille[y][x].part = NULL;  
                            grille[y+1-c][x-1].element = LIQUID;
                            grille[y+1-c][x-1].part = part_neighbour;
                        }
                    }
                    else
                    {
                        part_to_update->pos_y_norm += 1;
                        part_to_update->pos_x_norm -= 1;
                        part_to_update->box.y+=PARTICULE_SIZE;
                        part_to_update->box.x-=PARTICULE_SIZE;
                        part_to_update->hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].part = NULL;
                        grille[y+1][x-1].element = SAND;
                        grille[y+1][x-1].part = part_to_update;
                    } 
                }
                break;
            }
        }
        if(x+1<GRID_WIDTH)//Check if index of array will exist, en bas à droite
        {
            if(((grille[y+1][x+1].element == VOID) || (grille[y+1][x+1].element == LIQUID)))//Sinon si la place en bas à droite est libre 
            {
                if(part_to_update->hasbeenupdated == SDL_FALSE)
                {
                    if(grille[y+1][x+1].element == LIQUID)
                    {
                        Particule* part_neighbour = grille[y+1][x+1].part;
                        if(part_neighbour->hasbeenupdated == SDL_FALSE)
                        {
                            int c = 0;
                            while (grille[y+1-c][x+1].element != VOID)
                            {
                                c++;
                            }
                            part_neighbour->pos_y_norm -= c;
                            part_neighbour->box.y -= PARTICULE_SIZE*c;
                            part_neighbour->hasbeenupdated = SDL_TRUE;
                            part_to_update->pos_y_norm += 1; 
                            part_to_update->pos_x_norm += 1; 
                            part_to_update->box.x += PARTICULE_SIZE; 
                            part_to_update->box.y += PARTICULE_SIZE;
                            part_to_update->hasbeenupdated = SDL_TRUE;
                            grille[y+1][x+1].element = SAND;
                            grille[y+1][x+1].part = part_to_update;
                            grille[y][x].element = VOID;
                            grille[y][x].part = NULL;
                            grille[y+1-c][x+1].element = LIQUID;
                            grille[y+1-c][x+1].part = part_neighbour;
                        }
                    }
                    else 
                    {
                        part_to_update->pos_y_norm += 1;
                        part_to_update->pos_x_norm += 1;
                        part_to_update->box.y += PARTICULE_SIZE;
                        part_to_update->box.x += PARTICULE_SIZE;
                        part_to_update->hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].part = NULL;
                        grille[y+1][x+1].element = SAND;
                        grille[y+1][x+1].part = part_to_update;
                    }
                }
                break;
            }
        }
        break;
        
    case LIQUID:
        if(grille[y+1][x].element == VOID)//Si la place en bas est libre
        {
            if(part_to_update->hasbeenupdated == SDL_FALSE) //On update sa pos
            {
                part_to_update->pos_y_norm += 1;
                part_to_update->box.y += PARTICULE_SIZE;
                part_to_update->hasbeenupdated = SDL_TRUE;
                grille[y][x].element = VOID;
                grille[y][x].part = NULL;
                grille[y+1][x].element = LIQUID;
                grille[y+1][x].part = part_to_update;
            }
            break;
        }
        if (x-1 >=0)
        {
            if(grille[y+1][x-1].element == VOID)//Sinon si la place en bas à gauche est libre
            {
                if(part_to_update->hasbeenupdated == SDL_FALSE)//On update sa pos
                {
                    part_to_update->pos_y_norm += 1;
                    part_to_update->pos_x_norm -= 1;
                    part_to_update->box.y+=PARTICULE_SIZE;
                    part_to_update->box.x-=PARTICULE_SIZE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].part = NULL;
                    grille[y+1][x-1].element = LIQUID;
                    grille[y+1][x-1].part = part_to_update;
                }
                break;
            }
        }
        if (x+1<GRID_WIDTH)
        {
            if(grille[y+1][x+1].element == VOID)//Sinon si la place en bas à droite est libre 
            {
                if(part_to_update->hasbeenupdated == SDL_FALSE)
                {
                    part_to_update->pos_y_norm += 1;
                    part_to_update->pos_x_norm += 1;
                    part_to_update->box.y+=PARTICULE_SIZE;
                    part_to_update->box.x+=PARTICULE_SIZE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].part = NULL;
                    grille[y+1][x+1].element = LIQUID;
                    grille[y+1][x+1].part = part_to_update; 
                }
                break;
            }
            if((grille[y][x+1].element == VOID) && (rand()%2 == 0))//On glisse ou à droite...
            {
                if(part_to_update->hasbeenupdated == SDL_FALSE)
                {
                    part_to_update->pos_x_norm += 1;
                    part_to_update->box.x+=PARTICULE_SIZE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].part = NULL;
                    grille[y][x+1].element = LIQUID;
                    grille[y][x+1].part = part_to_update;
                }
                break;
            }
        }
        if (x-1>=0)
        {
            if((grille[y][x-1].element == VOID) && ((x-1) >= 0))//Ou à gauche
            {
                if(part_to_update->hasbeenupdated == SDL_FALSE)
                {
                    part_to_update->pos_x_norm -= 1;
                    part_to_update->box.x-=PARTICULE_SIZE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].part = NULL;
                    grille[y][x-1].element = LIQUID;
                    grille[y][x-1].part = part_to_update;
                }
                break;
            }
        }    
        break;
    case FIRE:
    {
        part_to_update->update_counter++;
        if (grille[y+1][x].element == LIQUID) //Voisin du bas
        {
            Particule* part_neighbour = grille[y+1][x].part;
            if(part_neighbour->hasbeenupdated == SDL_FALSE)
            {
                //Fire becomes smoke
                part_to_update->element = SMOKE;
                part_to_update->hasbeenupdated = SDL_TRUE;
                part_to_update->update_counter = 0;
                DeleteParticule(part_neighbour);
                grille[y][x].element = SMOKE;
                grille[y+1][x].element = VOID;
                grille[y+1][x].part = NULL;
                current_particule--;
            }
        }
        if ((y-1)>=0 && part_to_update->hasbeenupdated == SDL_FALSE) //Voisin du haut, on check dabord si on peut regarder la mémoire, pas élégant, à fix
        {
            if(grille[y-1][x].element == LIQUID) //Voisin du haut
            {
                Particule* part_neighbour = grille[y-1][x].part;
                if(part_neighbour->hasbeenupdated == SDL_FALSE)
                {
                    part_to_update->element = SMOKE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                    part_to_update->update_counter = 0;
                    DeleteParticule(part_neighbour);
                    grille[y][x].element = SMOKE;
                    grille[y-1][x].element = VOID;
                    grille[y-1][x].part = NULL;
                    current_particule--;
                }
            }
        }
        if (x+1<GRID_WIDTH && part_to_update->hasbeenupdated == SDL_FALSE)
        {
            if(grille[y][x+1].element == LIQUID) //Voisin de droite
            {
                Particule* part_neighbour = grille[y][x+1].part;
                if(part_neighbour->hasbeenupdated == SDL_FALSE)
                {
                    part_to_update->element = SMOKE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                    part_to_update->update_counter = 0;
                    DeleteParticule(part_neighbour);
                    grille[y][x].element = SMOKE;
                    grille[y][x+1].element = VOID;
                    grille[y][x+1].part = NULL;
                    current_particule--;
                }
            }
        }
        if (x-1>=0 && part_to_update->hasbeenupdated == SDL_FALSE)
        {
            if (grille[y][x-1].element == LIQUID) //Voisin de gauche
            {
                Particule* part_neighbour = grille[y][x-1].part;
                if(part_neighbour->hasbeenupdated == SDL_FALSE)
                {
                    part_to_update->element = SMOKE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                    part_to_update->update_counter = 0;
                    DeleteParticule(part_neighbour);
                    grille[y][x].element = SMOKE;
                    grille[y][x-1].element = VOID;
                    grille[y][x-1].part = NULL;
                    current_particule--;
                }
            }
        }
        if(part_to_update->update_counter > 50)
        {
            if(grille[y][x+1].element == WOOD)//Droite, si il y a du bois à côté, on met le feu au bois 
            {
                Particule* part_neighbour = grille[y][x+1].part;
                if(part_to_update->hasbeenupdated == SDL_FALSE && part_neighbour->hasbeenupdated == SDL_FALSE)
                {
                    grille[y][x+1].element = FIRE;
                    part_neighbour->element = FIRE;
                    part_neighbour->hasbeenupdated = SDL_TRUE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                }
            }
            else if(grille[y][x-1].element == WOOD) //Gauche
            {
                Particule* part_neighbour = grille[y][x-1].part;
                if(part_to_update->hasbeenupdated == SDL_FALSE && part_neighbour->hasbeenupdated == SDL_FALSE)
                {
                    grille[y][x-1].element = FIRE;
                    part_neighbour->element = FIRE;
                    part_neighbour->hasbeenupdated = SDL_TRUE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                }
            }
            else if(grille[y+1][x].element == WOOD) //En bas
            {
                Particule* part_neighbour = grille[y+1][x].part;
                if(part_to_update->hasbeenupdated == SDL_FALSE && part_neighbour->hasbeenupdated == SDL_FALSE)
                {
                    grille[y+1][x].element = FIRE;
                    part_neighbour->element = FIRE;
                    part_neighbour->hasbeenupdated = SDL_TRUE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                }
            }
            else if(grille[y-1][x].element == WOOD) //En haut
            {
                Particule* part_neighbour = grille[y-1][x].part;
                if(part_to_update->hasbeenupdated == SDL_FALSE && part_neighbour->hasbeenupdated == SDL_FALSE)
                {
                    grille[y-1][x].element = FIRE;
                    part_neighbour->element = FIRE;
                    part_neighbour->hasbeenupdated = SDL_TRUE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                }
            }
        }
        if(part_to_update->update_counter > 200)//On se transforme en fumée
        {
            if(part_to_update->hasbeenupdated == SDL_FALSE)
            {
                grille[y][x].element = SMOKE;
                part_to_update->element = SMOKE;
                part_to_update->update_counter = 0;
                part_to_update->hasbeenupdated = SDL_TRUE;
            }
        }
        else if(grille[y+1][x].element == VOID) //Sinon on tombe
        {
            if(part_to_update->hasbeenupdated == SDL_FALSE)
            {
                part_to_update->pos_y_norm += 1;
                part_to_update->box.y += PARTICULE_SIZE;
                part_to_update->hasbeenupdated = SDL_TRUE;
                grille[y][x].element = VOID;
                grille[y][x].part = NULL;
                grille[y+1][x].element = FIRE;
                grille[y+1][x].part = part_to_update;
            }
        }
        break;
    }
    case SMOKE:
        if(y-1 >=0)//Si le haut n'a pas été atteint
        {
            if(grille[y-1][x].element == VOID)//Si la place en haut est libre
            {
                if(part_to_update->hasbeenupdated == SDL_FALSE) //On update sa pos
                {
                    part_to_update->pos_y_norm -= 1;
                    part_to_update->box.y -= PARTICULE_SIZE;
                    part_to_update->hasbeenupdated = SDL_TRUE;
                    grille[y][x].element = VOID;
                    grille[y][x].part = NULL;
                    grille[y-1][x].element = SMOKE;
                    grille[y-1][x].part = part_to_update;
                }
                break;
            }
            if(x-1>=0)
            {
                if(grille[y-1][x-1].element == VOID)//Sinon si la place en haut à gauche est libre
                {
                    if(part_to_update->hasbeenupdated == SDL_FALSE)//On update sa pos
                    {
                        part_to_update->pos_y_norm -= 1;
                        part_to_update->pos_x_norm -= 1;
                        part_to_update->box.y-=PARTICULE_SIZE;
                        part_to_update->box.x-=PARTICULE_SIZE;
                        part_to_update->hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].part = NULL;
                        grille[y-1][x-1].element = SMOKE;
                        grille[y-1][x-1].part = part_to_update;
                    }
                    break;
                }
            }
            if(x+1<GRID_WIDTH)
            {
                if(grille[y-1][x+1].element == VOID)//Sinon si la place en haut à droite est libre 
                {
                    if(part_to_update->hasbeenupdated == SDL_FALSE)
                    {
                        part_to_update->pos_y_norm -= 1;
                        part_to_update->pos_x_norm += 1;
                        part_to_update->box.y-=PARTICULE_SIZE;
                        part_to_update->box.x+=PARTICULE_SIZE;
                        part_to_update->hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].part = NULL;
                        grille[y-1][x+1].element = SMOKE;
                        grille[y-1][x+1].part = part_to_update; 
                    }
                    break;
                }
                if((grille[y][x+1].element == VOID) && rand()%2 == 0)//On glisse ou à droite...
                {
                    if(part_to_update->hasbeenupdated == SDL_FALSE)
                    {
                        part_to_update->pos_x_norm += 1;
                        part_to_update->box.x+=PARTICULE_SIZE;
                        part_to_update->hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].part = NULL;
                        grille[y][x+1].element = SMOKE;
                        grille[y][x+1].part = part_to_update;
                    }
                    break;
                }
            }
            if(x-1 >= 0)
            {
                if(grille[y][x-1].element == VOID)//Ou à gauche
                {
                    if(part_to_update->hasbeenupdated == SDL_FALSE)
                    {
                        part_to_update->pos_x_norm -= 1;
                        part_to_update->box.x -= PARTICULE_SIZE;
                        part_to_update->hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].part = NULL;
                        grille[y][x-1].element = SMOKE;
                        grille[y][x-1].part = part_to_update;
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
                    if(part_to_update->hasbeenupdated == SDL_FALSE)
                    {
                        part_to_update->pos_x_norm += 1;
                        part_to_update->box.x+=PARTICULE_SIZE;
                        part_to_update->hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].part = NULL;
                        grille[y][x+1].element = SMOKE;
                        grille[y][x+1].part = part_to_update;
                    }
                    break;
                }
            }
            if(x-1>=0)
            {
                if((grille[y][x-1].element == VOID) && ((x-1) >= 0))//Ou à gauche
                {
                    if(part_to_update->hasbeenupdated == SDL_FALSE)
                    {
                        part_to_update->pos_x_norm -= 1;
                        part_to_update->box.x -= PARTICULE_SIZE;
                        part_to_update->hasbeenupdated = SDL_TRUE;
                        grille[y][x].element = VOID;
                        grille[y][x].part = NULL;
                        grille[y][x-1].element = SMOKE;
                        grille[y][x-1].part = part_to_update;
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

void UpdateParticulesNumber(Mode mode, Element element_param)
{
    switch (mode)
    {
    /*case AUTO://Not usable 
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
        break;*/
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
                    if(TO_PARTCULE_SIZE(Mouse_y)+y < GRID_HEIGHT && TO_PARTCULE_SIZE(Mouse_x)+i < GRID_WIDTH)
                    {
                        if(grille[TO_PARTCULE_SIZE(Mouse_y)+y][TO_PARTCULE_SIZE(Mouse_x)+i].element == VOID  && (current_particule < PARTICULE_MAX)) //On check que l'emplacement est bien vide
                        {
                            Particule* created_part = AddParticule();
                            created_part->ID = current_particule;
                            created_part->element = element_param;
                            created_part->hasbeenupdated =SDL_TRUE;
                            created_part->box.w = PARTICULE_SIZE;
                            created_part->box.h = PARTICULE_SIZE;
                            created_part->box.x = Mouse_x+TO_PIXEL_SIZE(i);
                            created_part->box.y = Mouse_y+TO_PIXEL_SIZE(y);
                            created_part->pos_x_norm = TO_PARTCULE_SIZE(created_part->box.x);
                            created_part->pos_y_norm = TO_PARTCULE_SIZE(created_part->box.y);
                            created_part->update_counter = 0;
                            grille[created_part->pos_y_norm][created_part->pos_x_norm].element = element_param;
                            grille[created_part->pos_y_norm][created_part->pos_x_norm].part = created_part;
                            current_particule++;
                            frame_count = 0;
                        }
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
            for (int i = 0; i <= TO_PARTCULE_SIZE(cursor_pad); i++)
            {
                for (int y = 0; y <= TO_PARTCULE_SIZE(cursor_pad); y++)
                {
                    if(TO_PARTCULE_SIZE(Mouse_y)+y < GRID_HEIGHT && TO_PARTCULE_SIZE(Mouse_x)+i < GRID_WIDTH)
                    {
                        if(grille[TO_PARTCULE_SIZE(Mouse_y)+y][TO_PARTCULE_SIZE(Mouse_x)+i].element != VOID && grille[TO_PARTCULE_SIZE(Mouse_y)+y][TO_PARTCULE_SIZE(Mouse_x)+i].element != FLOOR)
                        {
                            Particule* part_to_delete = grille[TO_PARTCULE_SIZE(Mouse_y)+y][TO_PARTCULE_SIZE(Mouse_x)+i].part;
                            grille[TO_PARTCULE_SIZE(Mouse_y)+y][TO_PARTCULE_SIZE(Mouse_x)+i].element = VOID;
                            grille[TO_PARTCULE_SIZE(Mouse_y)+y][TO_PARTCULE_SIZE(Mouse_x)+i].part = NULL;
                            DeleteParticule(part_to_delete);
                            printf("test\n");
                            current_particule--;
                            frame_count = 0;
                        }    
                    }  
                }
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
        grille[GRID_HEIGHT-1][i].part = NULL;
        FloorAndWall[i].h = PARTICULE_SIZE;
        FloorAndWall[i].w = PARTICULE_SIZE;
        FloorAndWall[i].y = TO_PIXEL_SIZE((GRID_HEIGHT-1));
        FloorAndWall[i].x = TO_PIXEL_SIZE(i);
    }
    for (int i = 0; i<(GRID_HEIGHT-1); i++)
    {
        grille[GRID_HEIGHT-2-i][GRID_WIDTH-1].element = FLOOR;
        grille[GRID_HEIGHT-2-i][GRID_WIDTH-1].part = NULL;
        FloorAndWall[GRID_WIDTH+i].h = PARTICULE_SIZE;
        FloorAndWall[GRID_WIDTH+i].w = PARTICULE_SIZE;
        FloorAndWall[GRID_WIDTH+i].y = TO_PIXEL_SIZE((GRID_HEIGHT-2-i));
        FloorAndWall[GRID_WIDTH+i].x = TO_PIXEL_SIZE((GRID_WIDTH-1));
    }
}

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