#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "createur_fichier_sat.h"
#include "lecture_ecriture.h"

void fin_clause(FILE *f) {
    fprintf(f, "0\n");
}

void init_creation_fichier_sat(FILE *f, size_t dim) { // Mise en place 
    fprintf(f, "p cnf 4 %ld\n", dim*dim*dim);
    fprintf(stderr, "-- TODO -- %s %d : Penser à implémenter le calcul du nombre de clauses (p cnf 4 ld)\n", __FILE__, __LINE__ - 1);
    unsigned char i, j, k, l;
    // Une seule valeur par case
    for (i = 0; i < dim; ++i) { // lignes
        for (j = 0; j < dim; ++j) { // colonnes
            for (k = 1; k <= dim; ++k) { // valeur de case
                fprintf(f, "%ld ", get_bool(i, j, k, dim));
            }
            fin_clause(f);
            for (k = 1; k <= dim; ++k) {
                for (l = k + 1; l <= dim; ++l) {
                        fprintf(f, "-%ld -%ld ", get_bool(i, j, k, dim), get_bool(i, j, l, dim));
                        fin_clause(f);
                }
            }
        }
        // Une seule fois la même valeur pour toutes les lignes / colonnes
        for (k = 1; k <= dim; ++k) { // valeur de case (1 .. dim)
            for (j = 0; j < dim; ++j) {// Compteur de colonne pour appliquer la propriété aux 2 sens
                fprintf(f, "%ld ", get_bool(i, j, k, dim));
            }
            fin_clause(f);
            for (j = 0; j < dim; ++j) {// Compteur de ligne pour appliquer la propriété aux 2 sens
                fprintf(f, "%ld ", get_bool(j, i, k, dim));
            }
            fin_clause(f);
        }
    }
}

char est_separateur(char c) {
    return (c == '>' || c == '<' || c == 'V' || c == '^' || c == ':' || c == '=');
}

void enregistrer_contrainte_separateur(unsigned char i, unsigned char j, __uint16_t contraintes[], char c, size_t dim) {
    i /= 2; // l j >< l j-1
    j /= 2; // c j >< c j-1
    __uint16_t contrainte;
    switch (c) {
        case '>':
            contrainte = ((i*dim + j) << 7) + i*dim + j+1;
            break;
        case '<':
            contrainte = ((i*dim + j+1) << 7) + i*dim + j;
            break;
        case 'V':
            contrainte = ((i*dim + j) << 7) + (i+1)*dim + j;
            break;
        case '^':
            contrainte = (((i+1)*dim + j) << 7) + i*dim + j;
            break;
        default:
            return;
    }
    contraintes[NOUVELLE_CONTRAINTE] = contrainte;
    NOUVELLE_CONTRAINTE++;
}

void enregistrer_contrainte_valeur(unsigned char i, unsigned char j, __uint16_t contraintes[], char c, size_t dim) {
    i /= 2;
    j /= 2;
    if ('0' <= c && c <= '9') {
        contraintes[NOUVELLE_CONTRAINTE] = 0b1000000000000000 + i*dim + j + c - '0';
        NOUVELLE_CONTRAINTE++;
    }
}

void recuperation_ruleset(FILE *f, __uint16_t contraintes[], size_t dim) {
    unsigned char i, j;
    char ligne[dim*2];
    for (i = 0; i < dim * dim + (dim-1)*(dim-1); ++i) {
        contraintes[i] = 0;
    }
    for (i = 0; i < dim; ++i) {
        if (lire_ligne(f, ligne) == lecture_ligne_fin_fichier) break;
        for (j = 0; j < dim; ++j) {
            enregistrer_contrainte_separateur(i, j, contraintes, ligne[j], dim);
            enregistrer_contrainte_valeur(i, j, contraintes, ligne[j], dim);
            if (ligne[j] == '\n') break;
        }
    }
}

void application_ruleset(FILE *f) {

}