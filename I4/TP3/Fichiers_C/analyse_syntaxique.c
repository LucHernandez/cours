#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"

#define crash_with(txt) {fprintf(stderr, txt);fprintf(stderr, "Colonne %d\n", lexeme_courant().colonne);exit(1);}

void analyser(char *fichier, double *resultat) {
    demarrer(fichier);
    rec_exp();
    printf("L'expression fournie est correcte\n");
}

void rec_exp() {
    printf("Called : %s\n",__func__);
    rec_eag();
    if (!fin_de_sequence()) {
        crash_with("Expression mal formée\n");
    }
}

void rec_eag() {
    printf("Called : %s\n",__func__);
    rec_seq_terme();
}

void rec_seq_terme() {
    printf("Called : %s\n",__func__);
    rec_terme();
    rec_suite_seq_terme();
}

void rec_suite_seq_terme() {
    printf("Called : %s\n",__func__);
    Nature_Lexeme nat = rec_op();
    if (nat == PLUS || nat == MOINS) {
        avancer();
        if (fin_de_sequence()) {
            crash_with("Expression non finie\n");
        }
        rec_terme();
        rec_suite_seq_terme();
    }
}

void rec_terme() {
    printf("Called : %s\n",__func__);
    rec_seq_facteur();
}

void rec_seq_facteur() {
    printf("Called : %s\n",__func__);
    rec_facteur();
    rec_suite_seq_facteur();
}

void rec_suite_seq_facteur() {
    printf("Called : %s\n",__func__);
    Nature_Lexeme nat = rec_op();
    if (nat == MUL || nat == DIVISION) {
        printf("op2 trouvé\n");
        avancer();
        rec_facteur();
        rec_suite_seq_facteur();
    }
}

void rec_facteur() {
    printf("Called : %s\n",__func__);
    Nature_Lexeme nat = lexeme_courant().nature;
    switch (nat) {
        case ENTIER:
            printf("Entier trouvé\n");
        break;
        case PARO:
            avancer();
            rec_eag();
            if (fin_de_sequence()) {
                crash_with("Expression non finie\n");
            }
            if (lexeme_courant().nature != PARF) {
                crash_with("Parenthèse fermée attendue\n");
            }
        break;
        default:
            crash_with("Entier ou parenthèse attendus\n");
        break;
    }
    avancer();
}

Nature_Lexeme rec_op() {
    printf("Called : %s\n",__func__);
    switch (lexeme_courant().nature) {
        case DIVISION:
        case PLUS:
        case MOINS:
        case MUL:
            printf("Operateur trouve\n");
            return lexeme_courant().nature;
        break;
        default:
            return EPSILON;
        break;
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
                crash_with("Erreur syntaxique: Format (eaep op eaep) attendu\n");
            }
            printf("PARF\n");
        } break;
        default: {
            crash_with("Erreur syntaxique: eaep non fourni\n");
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
                crash_with("Fun fact: On ne peut pas diviser un reel par 0\n");
            }
            (*resultat) /= val;
            break;
        case MUL:
            (*resultat) *= val;
            break;
        default:
            crash_with("Le programme ne devrait pas passer autre chose qu'un opérateur en argument, Y A UN PROBLEME LUC YOUHOU\n");
    } 
}