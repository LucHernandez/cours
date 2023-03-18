#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "type_variable.h"
#include "stdlib.h"

Variable *tas[];
unsigned int variables_amount;

/**
 * @brief Initialize le tableau pour amount variables
 * 
 * @param amount nombre de variables dans le tas
 */
void initialiser_tas(size_t amount);

/**
 * @brief Ajoute une valeur dans le tas
 * 
 * @param nom nom de la variable
 * @param val val de la variable
 */
void ajouter_val(char *nom, int val);

/**
 * @brief Get the val object
 * 
 * @param nom de la variable
 * @return int valeur associée au nom
 */
int get_val(char *nom);

#endif