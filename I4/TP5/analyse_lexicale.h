#ifndef _ANALYSE_LEXICALE_H_
#define _ANALYSE_LEXICALE_H_

/* ------------------------------------------------------------------------
-- paquetage machine_lexemes
--
-- analyse lexicale d'une expression arithmetique
--
-- P.Habraken - 18/01/2010
-- 
-- 2 aout 2006 - PH :
-- remplacement record a champs variants par record "plat"
------------------------------------------------------------------------ */

typedef enum {
	ERREUR_CAR,             // caractere incorrect
	CHIFFRE,	 		        // chiffre 
	SYMBOLE,	 		       // symbole
   C_FIN_SEQUENCE,      // caractere de fin de sequence     
   PARENTHESE,         // Parenthese
   SEPAFF,            // Point virgule ?
   CARACTERE,        // Caractère composant un IDF
   AFF,             // Symbole d'affectation
} Nature_Caractere;  

typedef enum { 
   ENTIER,                  // sequence de chiffres
   PLUS,                   // +
   MOINS,                 // -
   MUL,                  // *
   DIVISION,            // /
   FIN_SEQUENCE,       // pseudo lexeme ajoute en fin de sequence
   PARO,              // ouverture de parenthese
   PARF,             // fermeture de parenthese
   EPSILON,         // Cas ou ca n'est pas un operateur
   IDF,            // Identifiant (nom de variable)
   SEPARATEUR,    // Séparateur utilisé en fin d'affectation
   AFFECTATEUR,  // Symbole pour dire qu'on fait une affectation
} Nature_Lexeme;

typedef struct { 
   Nature_Lexeme nature;        // nature du lexeme
   unsigned int ligne;         // numero de ligne
   unsigned int colonne;      // numero de colonne
   char chaine[256];         // chaine de caracteres
   double valeur;           // valeur d'un entier
} Lexeme; 

void afficher(Lexeme l);

void demarrer(char *nom_fichier);
      // e.i. : indifferent
     // e.f. : la sequence de lexemes est lue dans le fichier designe par
    //        nom_fichier
   //        fin_de_sequence <=> lexeme_courant.nature = FIN_SEQUENCE
  //        (non fin_de_sequence) => lexeme courant est le premier
 //        lexeme de la sequence
//        l'exception Erreur_Lexicale est levee en cas d'erreur

void avancer();
      // pre-condition : la machine sequentielle est demarree
     // e.i. : on pose i = rang du lexeme_courant :
    //        (non fin_de_sequence)
   //        et (non lexeme_courant.nature = FIN_SEQUENCE)
  // e.f. : fin_de_sequence <=> lexeme_courant.nature = FIN_SEQUENCE
 //        (non fin_de_sequence) => lexeme_courant est le lexeme i+1
//        l'exception Erreur_Lexicale est levee en cas d'erreur

Lexeme lexeme_courant();
    // pre-condition : la machine sequentielle est demarree
   // lexeme_courant est :
  // . le pseudo lexeme FIN_SEQUENCE si fin_de_sequence
 // . le pseudo lexeme ERREUR si une erreur a ete detectee
// . le lexeme de rang i sinon

int fin_de_sequence();
   // pre-condition : la machine sequentielle est demarree
  // fin_de_sequence vaut :
 // . vrai si tous les lexemes de la sequence ont ete reconnus
// . faux sinon

void arreter();
 // e.i. : la machine sequentielle est demarree
// e.f. : la machine sequentielle est arretee

char *Nature_vers_Chaine (Nature_Lexeme nature);

#endif
