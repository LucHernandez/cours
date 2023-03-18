#ifndef _ANALYSE_SYNTAXIQUE_H_
#define _ANALYSE_SYNTAXIQUE_H_

#include "analyse_lexicale.h"
#include "type_ast.h"

/**
 * @brief Analyse syntaxiquement un fichier
 * @param fichier Fichier à analyser
 */
void analyser (char *fichier, Ast *ast_resultat);

void rec_exp();
void rec_eag();
void rec_seq_terme();
void rec_suite_seq_terme();
void rec_terme();
void rec_seq_facteur();
void rec_suite_seq_facteur();
void rec_facteur();
void rec_AFF();
void rec_affectation();
void rec_SEPAFF();
void rec_idf();
Nature_Lexeme rec_op();

double rec_eaep();
void calculer_resultat(double *resultat, Nature_Lexeme ope_preced, double val);

#endif