#include <stdio.h>

#include "lecture_ecriture.h"
#include "tools.h"

FILE* ouvrir_fichier(char *nom_fichier, char *mode) 
{
    if (!nom_fichier) crash_with("%s : Nom de fichier incorrect\n", __func__);
    FILE *f = fopen(nom_fichier, mode);
    if (!f) crash_with("%s : Impossible d'ouvrir le fichier %s", __func__, mode);
    return f;
}

lecture_ligne_etat lire_ligne(FILE *f, char destination[]) 
{
    if (feof(f)) {
        return lecture_ligne_fin_fichier;
    }
    fscanf(f, "%s\n", destination);
    return lecture_ligne_OK;
}

size_t get_dimension(FILE *f) {
    int dim;
    fscanf(f, "%d\n", &dim);
    return (size_t) dim;
}