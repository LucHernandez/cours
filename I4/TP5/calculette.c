#include <stdio.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"
#include "ast_construction.h"
#include "ast_parcours.h"
#include "type_ast.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "1 paramètre attendus, %d reçu\n", argc - 1);
        return 1;
    }
    Ast ast_resultat;
    analyser(argv[1], &ast_resultat);
    printf("L'analyse a réussie !\nast:\n");
    afficher_ast(ast_resultat);
    printf("\nLe résultat de l'expression est %d\n", evaluation(ast_resultat));

    return 0;
}
