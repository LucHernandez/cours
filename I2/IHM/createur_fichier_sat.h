#ifndef _CREATEUR_FICHIER_SAT_H_
#define _CREATEUR_FICHIER_SAT_H_

#include <stdio.h>
#include <stdlib.h>

__uint64_t NOUVELLE_CONTRAINTE = 0;

// Met en place les règles de base pour le fichier SAT
void init_creation_fichier_sat(FILE *f, size_t dim);

char est_separateur(char c);

void enregistrer_contrainte_separateur(unsigned char i, unsigned char j, __uint16_t contraintes[], char c, size_t dim);

void enregistrer_contrainte_valeur(unsigned char i, unsigned char j, __uint16_t contraintes[], char c, size_t dim);

/*

x & 1111 0000 0000 0000 -> (x & 0000 1111 1111 0000) >> 4 indique la position du chiffre
                           x & 0000 0000 0000 1111 valeur à placer à la position
sinon                   -> (x & 1111 1111 0000 0000)

*/

// Récupère le ruleset du fichier humain et le stocke
void recuperation_ruleset();

void application_ruleset(FILE *f);

#endif