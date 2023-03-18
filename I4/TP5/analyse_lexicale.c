/* ------------------------------------------------------------------------
-- paquetage analyse_lexicale
--
-- analyse lexicale d'une expression arithmetique
--
-- J-P. Peyrin, G. Serasset (version initiale) : janvier 1999
-- P.Habraken - 18/01/2010
--
-- 10 juin 2006 - PH :
-- remplacement record a champs variants par record "plat"
-- remplacement traitement iteratif par automate
--
-- Aout 2016 - LM : version C
------------------------------------------------------------------------ */

#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

/* --------------------------------------------------------------------- */


/* Les variables et fonctions locales au module */

Lexeme lexeme_en_cours;	/* le lexeme courant */

void ajouter_caractere (char *s, char c);
Nature_Caractere nature_caractere (char c);
int est_separateur(char c );
int est_chiffre(char c );
int est_symbole(char c );
int est_parenthese(char c);
void reconnaitre_lexeme();
int est_caractere(char c);
int est_SEPAFF(char c);
int est_affectation(char c);

/* --------------------------------------------------------------------- */

void demarrer(char *nom_fichier) {
   demarrer_car(nom_fichier);
   avancer();
}

/* --------------------------------------------------------------------- */

void avancer() {
   reconnaitre_lexeme();
} 

/* --------------------------------------------------------------------- */

Lexeme lexeme_courant() {
   return lexeme_en_cours;
} 

/* --------------------------------------------------------------------- */

int fin_de_sequence() {
   return lexeme_en_cours.nature == FIN_SEQUENCE;
}

/* --------------------------------------------------------------------- */

void arreter() {
   arreter_car();
}

/* --------------------------------------------------------------------- */

unsigned int ten_power(unsigned char p) {
   int ret = 1;
   for (; p > 0; --p) {
      ret *= 10;
   }
   return ret;
}

// reconnaissance d'un nouveau lexeme
// etat initial : le caractere courant est soit separateur 
//                soit le 1er caractere d'un lexeme
// etat final : 
//       - un nouveau lexeme est reconnu dans lexeme_en_cours
//       - le caractere courant est soit la fin de fichier, 
//		soit un separateur,  soit le 1er caractere d'un lexeme
void reconnaitre_lexeme() {
   typedef enum {E_INIT, E_ENTIER, E_IDF, E_FIN} Etat_Automate;
   Etat_Automate etat=E_INIT;

   // on commence par lire et ignorer les separateurs
   while (est_separateur(caractere_courant())) {
      avancer_car();
   }

   lexeme_en_cours.chaine[0] = '\0';

   // on utilise ensuite un automate pour reconnaitre et construire le prochain lexeme
   char virgule_state = 0;
   char nom_variable[50];
   unsigned char place_nom_variable = 0;
   while (etat != E_FIN) {
	   switch (etat) {
         case E_INIT: // etat initial
         // Le cas E_INIT va etre le cas ou on peut dire la ligne et la colonne de debut du lexeme
			   switch(nature_caractere(caractere_courant())) {
               case C_FIN_SEQUENCE: // On est bien à la fin d'une sequence / lexeme, on peut s'en aller
             	   lexeme_en_cours.nature = FIN_SEQUENCE;
                  etat = E_FIN;
					break;
				   case CHIFFRE: { // On a soit des chiffres soit des operateurs ( = symboles )
		     		   lexeme_en_cours.nature = ENTIER;
                  lexeme_en_cours.ligne = numero_ligne();
                  lexeme_en_cours.colonne = numero_colonne();
		     		   ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                  etat = E_ENTIER;
                  if (caractere_courant() == '.') {
                     lexeme_en_cours.valeur = 0;
                     lexeme_en_cours.nature = ENTIER;
                     virgule_state++;
                     avancer_car();
                     break;
                  }
                  lexeme_en_cours.valeur = caractere_courant() - '0';
		   		   avancer_car();
               } break;
				   case SYMBOLE: {
		       	   lexeme_en_cours.ligne = numero_ligne();
                  lexeme_en_cours.colonne = numero_colonne();
		       	   ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                  switch (caractere_courant()) {
               	   case '+':
               		   lexeme_en_cours.nature = PLUS;
               		   etat = E_FIN;
			   		   break;
               	   case '-':
               		   lexeme_en_cours.nature = MOINS;
               		   etat = E_FIN;
			   		   break;
               	   case '*':
               		   lexeme_en_cours.nature = MUL;
               		   etat = E_FIN;
			   		   break;
                     case '/':
                        lexeme_en_cours.nature = DIVISION;
                        etat = E_FIN;
                     break;
		       		   default:
						      printf("Erreur_Lexicale");
				 		      exit(0);
				 	   }
		   		   avancer_car();
               } break;
               case PARENTHESE: {
                  lexeme_en_cours.ligne = numero_ligne();
                  lexeme_en_cours.colonne = numero_colonne();
                  ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                  switch (caractere_courant()) {
                     case '(' : {
                        lexeme_en_cours.nature = PARO;
                        etat = E_FIN;
                     } break;
                     case ')' : {
                        lexeme_en_cours.nature = PARF;
                        etat = E_FIN;
                     } break;
                  }
                  avancer_car();
               } break;
               case CARACTERE: {
                  etat = E_IDF;
                  lexeme_en_cours.nature = IDF;
                  nom_variable[place_nom_variable++] = caractere_courant();
                  avancer_car();
               } break;
               case SEPAFF: {
                  lexeme_en_cours.nature = SEPARATEUR;
                  avancer_car();
                  etat = E_FIN;
               } break;
               case AFF: {
                  lexeme_en_cours.nature = AFFECTATEUR;
                  avancer_car();
                  etat = E_FIN;
               } break;
				   default:
		            printf("Erreur_Lexicale\n");
		            exit(0);
		      }
		break;
		case E_ENTIER:  // reconnaissance d'un entier
			switch(nature_caractere(caractere_courant())) {
			   case CHIFFRE:
               ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
               if (caractere_courant() == '.') { // Gestion cas lecture de point
                  if (virgule_state) {
                     printf("Erreur Lexicale\n");
                     exit(0);
                  }
                  virgule_state = 1;
                  avancer_car();
                  continue;
               }
               lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
               if (virgule_state) {
                  virgule_state++;
               }
               etat = E_ENTIER;
               avancer_car ();
				break;
				default:
               if (virgule_state)
                  lexeme_en_cours.valeur /= ten_power(virgule_state - 1);
               etat = E_FIN;
          	}
      case E_FIN:  // etat final
		break;
      case E_IDF: {
         if (nature_caractere(caractere_courant()) == CARACTERE) {
            if (place_nom_variable >= 49) {
               fprintf(stderr, "Erreur Lexicale: nom de variable trop long");
            }
            nom_variable[place_nom_variable++] = caractere_courant();
            avancer_car();
         } else {
            nom_variable[place_nom_variable] = '\0';
            avancer_car();
            etat = E_FIN;
         }
      }	break;    
	   } // fin du switch(etat)
   } // fin du while (etat != fin)
}

/* --------------------------------------------------------------------- */

// cette fonction ajoute le caractere c a la fin de la chaine s 
// (la chaine s est donc modifiee)
 
void ajouter_caractere (char *s, char c) {
	int l;
	l = strlen(s);
	s[l] = c;
	s[l+1] = '\0';
}

/* --------------------------------------------------------------------- */

Nature_Caractere nature_caractere (char c) {
	if (fin_de_sequence_car(c)) return C_FIN_SEQUENCE;
	if (est_chiffre(c))         return CHIFFRE;
	if (est_symbole(c))         return SYMBOLE;
   if (est_parenthese(c))      return PARENTHESE;
   if (est_SEPAFF(c))          return SEPAFF;
   if (est_caractere(c))       return CARACTERE;
   if (est_affectation(c))     return AFF;
	return ERREUR_CAR;
}

/* --------------------------------------------------------------------- */

// vaut vrai ssi c designe un caractere separateur
int est_separateur(char c) { 
   return c == ' ' || c == '\t' || c == '\n';
}

/* --------------------------------------------------------------------- */

// vaut vrai ssi c designe un caractere chiffre
int est_chiffre(char c) {
   return (c >= '0' && c <= '9') || c == '.';
}

/* --------------------------------------------------------------------- */

// vaut vrai ssi c designe un caractere correspondant a un symbole arithmetique
int est_symbole(char c)  {
   switch (c) {
      case '+':  
	 	case '-':  
	 	case '*':
	 	case '/':
         return 1;
      default:
         return 0;
   } 
}

/* --------------------------------------------------------------------- */

int est_parenthese(char c) {
   return (c == '(' || c == ')') ? 1 : 0;
}

int est_caractere(char c) {
   return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

int est_SEPAFF(char c) {
   return (c == ';');
}

int est_affectation(char c) {
   return (c == '=');
}

// renvoie la chaine de caracteres correspondant a la nature du lexeme
char *Nature_vers_Chaine (Nature_Lexeme nature) {
	switch (nature) {
		case ENTIER: return "ENTIER";
		case PLUS: return "PLUS";
      case MOINS: return "MOINS";            
      case MUL: return "MUL";
      case DIVISION: return "DIVISION";
      case PARO: return "PARO";
      case PARF: return "PARF";
      case FIN_SEQUENCE: return "FIN_SEQUENCE";
      case IDF: return "IDENTIFIANT";
      case SEPARATEUR: return "SEPARATEUR";
      case AFFECTATEUR: return "AFFECTATEUR";
      default: return "ERREUR";            
	}
} 

/* --------------------------------------------------------------------- */

// affiche a l'ecran le lexeme l
void afficher(Lexeme l) {
   switch (l.nature) {
      case FIN_SEQUENCE: 
      break;
      default: 
         printf("(ligne %d, ", l.ligne);
         printf("colonne %d) : ",l.colonne);
	      printf("[");
         printf("nature = %s", Nature_vers_Chaine(l.nature));
         printf(", chaine = %s", l.chaine);
         switch(l.nature) {
            case ENTIER:
               printf(", valeur = %f", l.valeur);
            default:
            break;
         }
	   printf("]");
	}
}

/* --------------------------------------------------------------------- */