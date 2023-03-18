#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdio.h>
#include <stdlib.h>

#define DIM_MAX 9

#define crash_with(...) {fprintf(stderr, __VA_ARGS__); exit(1);}
#define get_bool(ligne, colonne, valeur, dimension) (ligne*dimension*dimension + colonne*dimension + valeur)
#define get_ligne(n, dim)
#define get_colonne(n, dim)
#define get_valeur(n, dim)

#endif