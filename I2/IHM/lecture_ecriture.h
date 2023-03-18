#ifndef _LECTURE_ECRITURE_H_
#define _LECTURE_ECRITURE_H_

#include <stdio.h>

/**
 * @brief Ouvre le fichier
 * 
 * @param f
 * @param nom_fichier 
 * @param mode "r", "w", "rw"
 * @return char 
 */
FILE* ouvrir_fichier(char *nom_fichier, char *mode);


typedef enum {
    lecture_ligne_OK,
    lecture_ligne_fin_fichier,
    lecture_ligne_echouee,
} lecture_ligne_etat;

/**
 * @brief Passe la ligne suivante dans le buffer destination
 * 
 * @param f Fichier à lire
 * @param destination Buffer de taille n à déciser
 * @return lecture_ligne_etat
 */
lecture_ligne_etat lire_ligne(FILE *f, char destination[]);

/**
 * @brief Récupère la dimension du Futoshiki
 * 
 * @param f 
 * @return size_t 
 */
size_t get_dimension(FILE *f);

#endif