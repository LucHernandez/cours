#ifndef _ANALYSE_SYNTAXIQUE_H_
#define _ANALYSE_SYNTAXIQUE_H_

#include "analyse_lexicale.h"

/**
 * @brief Analyse syntaxiquement un fichier
 * @param fichier Fichier à analyser
 */
void analyser (char *fichier, double *resultat);
void calculer_resultat(double *resultat, Nature_Lexeme ope_preced, double val);

#endif