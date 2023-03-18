#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tools.h"
#include "lecture_ecriture.h"
#include "createur_fichier_sat.h"

int main (int argc, char **argv) {
    if (argc != 2) crash_with("Erreur : Nombre d'arguments incorrect, 1 attendu, %d fournis\n", argc);

    // On charge le fichier lisible
    FILE *futoshiki_file;
    futoshiki_file = ouvrir_fichier(argv[1], "r");

    // On récupère les informations du fichier
    size_t dim = get_dimension(futoshiki_file);
    if (dim > DIM_MAX || dim <= 0) {
        fclose(futoshiki_file);
        crash_with("Erreur : Dimension non prise en compte\n0 < dim < %zu ; dim fournie = %d", dim, DIM_MAX);
    }

    fprintf(stderr, "-- TODO -- %s %d : Mettre en place la lecture du fichier Humain\n", __FILE__, __LINE__ - 1);

    /*
        On décide de stocker chaque contrainte dans un entier en 16 bits
        1000 0000 0000 0000
    */

    __uint16_t contraintes[dim * dim + (dim-1)*(dim-1)];
    recuperation_ruleset(futoshiki_file, contraintes, dim);
    for (unsigned int i = 0; contraintes[i] != 0; ++i) {
        printf("%d\n", contraintes[i]);
    }
    ///////////////////////////////////////////
    //                                       //       
    // ICI GERER LA RECUPERATION DES DONNEES //
    //                                       //
    ///////////////////////////////////////////

    fclose(futoshiki_file);

    futoshiki_file = ouvrir_fichier("futoshiki_sat", "w");
    init_creation_fichier_sat(futoshiki_file, dim);
    
    return 0;
}