#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"
#include "type_ast.h"
#include "ast_construction.h"

#define crash_with(txt) {fprintf(stderr, txt);fprintf(stderr, "Colonne %d\n", lexeme_courant().colonne);exit(1);}

void analyser(char *fichier, Ast *ast_res) {
    demarrer(fichier);
    rec_affectation();
    //rec_exp(ast_res);
    printf("L'expression fournie est correcte\n");
}

void rec_affectation() {
    printf("Called : %s\n",__func__);
    Ast ast_res; // Uniquement pour que le correcteur syntaxique ne me crie pas dessus
    rec_idf();
    rec_AFF();
    rec_eag(ast_res);
    rec_SEPAFF();
}

void rec_AFF() {
    printf("Called : %s\n",__func__);
    if (lexeme_courant().nature != AFFECTATEUR) {
        crash_with("= attendu\n");
    }
    avancer();
}

void rec_idf() {
    printf("Called : %s\n",__func__);
    if (lexeme_courant().nature != IDF) {
        crash_with("Identificateur attendu\n");
    }
    avancer();
}

void rec_SEPAFF() {
    printf("Called : %s\n",__func__);
    if (lexeme_courant().nature != SEPARATEUR) {
        crash_with("; attendu\n");
    }
    avancer();
}

void rec_exp(Ast *ast_res) {
    printf("Called : %s\n",__func__);
    rec_eag(ast_res);
    if (!fin_de_sequence()) {
        crash_with("Expression mal formée\n");
    }
}

void rec_eag(Ast *ast_res) {
    printf("Called : %s\n",__func__);
    rec_seq_terme(ast_res);
}

void rec_seq_terme(Ast *ast_res) {
    printf("Called : %s\n",__func__);
    Ast A1;
    rec_terme(&A1);
    rec_suite_seq_terme(A1, ast_res);
}

void rec_suite_seq_terme(Ast Ag, Ast *ast_res) {
    Ast Ad, A1;
    TypeOperateur Op;
    printf("Called : %s\n",__func__);
    Nature_Lexeme nat = rec_op();
    if (nat == PLUS || nat == MOINS) {
        // printf("op1 trouvé\n");
        if (nat == PLUS) {
            Op = N_PLUS;
        } else {
            Op = N_MOINS;
        }
        avancer();
        if (fin_de_sequence()) {
            crash_with("Expression non finie\n");
        }
        rec_terme(&Ad);
        A1 = creer_operation(Op, Ag, Ad);
        rec_suite_seq_terme(A1, ast_res);
    }
    else {
        *ast_res = Ag;
    }
}

void rec_terme(Ast *ast_res) {
    printf("Called : %s\n",__func__);
    rec_seq_facteur(ast_res);
}

void rec_seq_facteur(Ast *ast_res) {
    printf("Called : %s\n",__func__);
    Ast A1;
    rec_facteur(&A1);
    rec_suite_seq_facteur(A1, ast_res);
}

void rec_suite_seq_facteur(Ast Ag, Ast *ast_res) {
    printf("Called : %s\n",__func__);
    Ast Ad, A1;
    TypeOperateur Op;
    Nature_Lexeme nat = rec_op();
    if (nat == MUL || nat == DIVISION) {
        if (nat == MUL) {
            Op = N_MUL;
        } else {
            Op = N_DIV;
        }
        printf("op2 trouvé\n");
        avancer();
        rec_facteur(&Ad);
        A1 = creer_operation(Op, Ag, Ad);
        rec_suite_seq_facteur(A1, ast_res);
    }
    else {
        *ast_res = Ag;
    }
}

void rec_facteur(Ast *ast_res) {
    printf("Called : %s\n",__func__);
    Nature_Lexeme nat = lexeme_courant().nature;
    switch (nat) {
        case ENTIER:
            *ast_res = creer_valeur(lexeme_courant().valeur);
            printf("Entier trouvé : %f\n", lexeme_courant().valeur);
        break;
        case IDF: {
            printf("IDF tourvé !\n");
        } break;
        case PARO:
            avancer();
            rec_eag(ast_res);
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
            printf("Operateur trouve : %s\n", lexeme_courant().chaine);
            return lexeme_courant().nature;
        break;
        default:
            return EPSILON;
        break;
    }
}