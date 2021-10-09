#include "Debug.h"

void PrintGrille(pixel** grille)
{
    FILE* fichier_dump = fopen("debug_dump.txt", "w");
    for(int i = 0; i<110; i++)
    {
        for(int y = 0; y<50; y++)
        {
            //if(grille[i][y].element != VOID)
                fprintf(fichier_dump, "[%d,%d],", grille[i][y].element, grille[i][y].ID);
        }
        fprintf(fichier_dump, "\n");
    }
    fclose(fichier_dump);
}