#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

enum blocLibre {Libre, Utilise};

struct bloc {
  int debut;
  int taille;
  enum blocLibre drapeau;
};
typedef struct bloc bloc;

#include "liste.h" //vous pouvez remplacer par votre implémentation de liste favorite

struct memoire {
  int tailleMot;
  int nbMots;
  Liste* listBlocs;
};
typedef struct memoire memoire;

/* Création d'une mémoire composéé de 'nbMots' mots de taille 'tailleMot' */
memoire creerMemoire (int tailleMot, int nbMots) {
  memoire m = {tailleMot, nbMots};
  m.listBlocs = initialisation();
  bloc a = {0, nbMots, Libre};
  insertion(m.listBlocs, a);
  return m;
}


/* bloc allocationMemoire (memoire mem, int tailleAAllouer) {

}

void liberationMemoire (memoire mem, bloc blocALiberer) {
  
} */

int main() {
  memoire a = creerMemoire(2, 32);

  afficherListe(a.listBlocs);

   

  return 0;
}
