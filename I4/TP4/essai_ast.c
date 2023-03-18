#include <stdio.h> 

#include "ast_construction.h"
#include "ast_parcours.h"

/*
— 2 + 3 * 5 - 2
— (2 + 3) * (5 - 2)
— 2 + 3 / (5 - 2)
— 3 / (5 - 2 - 3)
*/

int main() {

    Ast ast1, ast2, ast3, ast4, ast5, ast;

    ast1 = creer_valeur(2);
    ast2 = creer_valeur(3);
    ast3 = creer_valeur(5);
    ast4 = creer_operation(N_MUL, ast2, ast3);
    ast5 = creer_operation(N_PLUS, ast1, ast4);
    ast  = creer_operation(N_MOINS, ast5, ast3);

    printf("Arbre abstrait de l'expression\n");
    afficher_ast(ast); 
    printf("\n\nValeur de l'expression : %d\n", evaluation(ast));
    return 0;
}
