#include <stdio.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "1 paramètre attendus, %d reçu\n", argc - 1);
        return 1;
    }
    double resultat;
    analyser(argv[1], &resultat);

    printf("Le résultat de l'opération est %f\n", resultat);

    return 0;
}
