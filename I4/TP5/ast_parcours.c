#include <stdlib.h>
#include <stdio.h>

#include "type_ast.h"
#include "ast_parcours.h"

void aff_operateur(TypeOperateur op){
	switch (op) {
		case N_PLUS:
			printf("+") ;
			break;
		case N_MOINS:
			printf("-") ;
			break;
		case N_MUL:
			printf("*") ;
			break;
		case N_DIV:
			printf("/");
			break;
	} 
}

void afficher_ast(Ast expr) {
	switch (expr->nature) {
               case OPERATION:
                        printf("(");
                        afficher_ast(expr->gauche);
                        aff_operateur(expr->operateur) ;
                        afficher_ast(expr->droite);
                        printf(")");
			break ;
               case VALEUR:
                  	printf("%d", expr->valeur);
			break ;
	}
}

int evaluation(Ast expr)
{
    int Vg, Vd;
	switch (expr->nature) {
		case VALEUR:
			return expr->valeur;
		break;
		case OPERATION:
			Vg = evaluation(expr->gauche);
			Vd = evaluation(expr->droite);
			switch (expr->operateur) {
				case N_PLUS: return Vg + Vd;
				case N_MOINS: return Vg - Vd;
				case N_MUL: return Vg * Vd;
				case N_DIV:
					if (Vd == 0) {
						printf("Division par 0 impossible\n");
						exit(1);
					}
					return Vg / Vd;
			}
		break;
	}
    return -1 ;
}

