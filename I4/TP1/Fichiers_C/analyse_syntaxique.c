#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"

void analyser(char *fichier, double *resultat) {
    typedef enum {E_INIT, E_ENTIER, E_OPERATEUR} Etat_Automate;

    Etat_Automate etat = E_INIT;

    Lexeme current_lexeme;

    demarrer(fichier);

    Nature_Lexeme operateur_precedent = PLUS;

    while (!fin_de_sequence()) {
        current_lexeme = lexeme_courant();
        switch (etat) {
            case E_INIT:
                switch (current_lexeme.nature) {
                    case ENTIER:
                        *resultat = current_lexeme.valeur;
                        etat = E_ENTIER;
                        break;
                    case FIN_SEQUENCE:
                        break;
                    case MOINS:
                        operateur_precedent = MOINS;
                        *resultat = 0;
                        etat = E_OPERATEUR;
                        break;
                    case PLUS:
                    case DIVISION:
                    case MUL:
                        fprintf(stderr, "L'expression arithmétique ne doit pas commencer par un opérateur\n");
                        exit(1);
                }
                break;
            case E_ENTIER:
                switch (current_lexeme.nature) {
                    case ENTIER:
                        fprintf(stderr, "L'expression arithmétique ne doit pas comporter un entier suivi d'un entier\n");
                        exit(1);
                        break;
                    case FIN_SEQUENCE:
                        break;
                    case PLUS:
                    case MOINS:
                    case DIVISION:
                    case MUL:
                        etat = E_OPERATEUR;
                        operateur_precedent = current_lexeme.nature;
                        break;
                    default:
                        fprintf(stderr, "CAS A TRAITER, PROGRAMME MAL FAIT LIGNE %d\n", __LINE__);
                        exit(1);
                        break;
                }
                break;
            case E_OPERATEUR:
                switch (current_lexeme.nature) {
                    case FIN_SEQUENCE:
                        break;
                    case ENTIER:
                        etat = E_ENTIER;
                        calculer_resultat(resultat, operateur_precedent, current_lexeme.valeur);
                        break;
                    case PLUS:
                    case MOINS:
                    case DIVISION:
                    case MUL:
                        fprintf(stderr, "L'expression arithmétique ne doit pas comporter plusieurs opérateurs côte à côte\n");
                        exit(1);
                    default:
                        fprintf(stderr, "CAS A TRAITER, PROGRAMME MAL FAIT LIGNE %d\n", __LINE__);
                        exit(1);
                }
                break;
            default:
                fprintf(stderr, "CAS A TRAITER, PROGRAMME MAL FAIT LIGNE %d\n", __LINE__);
                exit(1);
        }
        avancer();
    }
    switch (etat) {
        case E_OPERATEUR:
            fprintf(stderr, "L'expression arithmétique ne doit pas finir par un opérateur\n");
            exit(1);
        case E_INIT:
            fprintf(stderr, "L'expression arithmétique ne doit pas être vide\n");
            exit(1);
        case E_ENTIER:
            printf("La syntaxe de l'expression arithmétique est valide !\n");
    }  
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