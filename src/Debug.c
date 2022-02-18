#include "Debug.h"

void PrintGrille(pixel** grille)
{
    FILE* fichier_dump = fopen("debug_dump.txt", "w");
    for(int i = 0; i<GRID_HEIGHT; i++)
    {
        for(int y = 0; y<50; y++)
        {
            //if(grille[i][y].element != VOID)
                fprintf(fichier_dump, "[%d],", grille[i][y].element);
        }
        fprintf(fichier_dump, "\n");
    }
    fclose(fichier_dump);
}