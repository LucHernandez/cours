#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"

void analyser(char *fichier, double *resultat) {
    demarrer(fichier);
    *resultat = rec_eaep();
    if (!fin_de_sequence()) {
        printf("Erreur : EAEP mal formée\n");
        exit(1);
    }
}

Nature_Lexeme rec_op() {
    switch (lexeme_courant().nature) {
        case DIVISION:
        case PLUS:
        case MOINS:
        case MUL:
            printf("OPE\n");
            return lexeme_courant().nature;
        default:
            fprintf(stderr, "Erreur syntaxique: Opérateur attendu\n");
            exit(1);
    }
}

double rec_eaep() {
    Lexeme lex_cour = lexeme_courant();
    double res = 0;
    double partie_droite;
    Nature_Lexeme terre_du_milieu;
    switch (lex_cour.nature) {
        case ENTIER: {
            printf("CHIFFRE\n");
            res = lex_cour.valeur;
        } break;
        case PARO: {
            printf("PARO\n");
            avancer();
            res = rec_eaep();
            terre_du_milieu = rec_op();
            avancer();
            partie_droite = rec_eaep();
            calculer_resultat(&res, terre_du_milieu, partie_droite);
            if (lexeme_courant().nature != PARF) {
                fprintf(stderr, "Erreur syntaxique: Format (eaep op eaep) attendu\n");
                exit(1);
            }
            printf("PARF\n");
        } break;
        default: {
            fprintf(stderr, "Erreur syntaxique: eaep non fourni\n");
            exit(1);
        } break;
    }
    avancer();
    return res;
}


void calculer_resultat(double *resultat, Nature_Lexeme ope_preced, double val) {
    switch (ope_preced) {
        case PLUS:
            (*resultat) += val;
            break;
        case MOINS:
            (*resultat) -= val;
            break;
        case DIVISION:
            if (val == 0) {
                fprintf(stderr, "Fun fact: On ne peut pas diviser un reel par 0\n");
                exit(1);
            }
            (*resultat) /= val;
            break;
        case MUL:
            (*resultat) *= val;
            break;
        default:
            fprintf(stderr, "Le programme ne devrait pas passer autre chose qu'un opérateur en argument, Y A UN PROBLEME LUC YOUHOU\n");
    } 
}