#ifndef _ANALYSE_SYNTAXIQUE_H_
#define _ANALYSE_SYNTAXIQUE_H_

#include "analyse_lexicale.h"

/**
 * @brief Analyse syntaxiquement un fichier
 * @param fichier Fichier à analyser
 */
void analyser (char *fichier, double *resultat);

void rec_exp();
void rec_eag();
void rec_seq_terme();
void rec_suite_seq_terme();
void rec_terme();
void rec_seq_facteur();
void rec_suite_seq_facteur();
void rec_facteur();
Nature_Lexeme rec_op();

double rec_eaep();
void calculer_resultat(double *resultat, Nature_Lexeme ope_preced, double val);

#endif