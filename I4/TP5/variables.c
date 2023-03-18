#include <stdio.h>
#include <stdlib.h>

#include "type_variable.h"
#include "variables.h"

void initialiser_tas(size_t amount) {
    variables_amount = amount;
    tas = malloc(sizeof(variable*)*amount);
    unsigned int i = 0;
    for(; i < amount; ++i) {
        tas[i] = malloc(sizeof(Variable));
    }
}

void ajouter_val() {
    static unsigned int i = 0;
    if (i > variables_amount - 1) {
        fprintf(stderr, "Trop de variables ajoutées par rapport à ce qui a été annoncé\n");
    }
}

