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

/* Calcule du nombre de mots libres dans la mémoire */
int nbreMotLibre(memoire m) {
  Element* courant;
  courant = m.listBlocs->premier;
  int total = 0;
  while (courant != NULL) {
    if (courant->data.drapeau == Libre) {
      total = total + courant->data.taille;
    }
    courant = courant->suivant;
  }
  return total;
}


bloc allocationMemoire (memoire mem, int tailleAAllouer) {
  bloc aAjouter;
  if (tailleAAllouer > mem.nbMots || tailleAAllouer > nbreMotLibre(mem)) {
    printf("Impossible d'allouer : Taille demandee superieur a la taille disponible\n");
    exit(EXIT_FAILURE);
  }
  else {
    Element* courant;
    courant = mem.listBlocs->premier;
    int i = 0;

    while (courant != NULL) {
      if (courant->data.drapeau == Libre && courant->data.taille >= tailleAAllouer) {
        aAjouter.debut = courant->data.debut;
        aAjouter.taille = tailleAAllouer;
        aAjouter.drapeau = Utilise;
        courant->data.debut = aAjouter.debut + aAjouter.taille;
        courant->data.taille = courant->data.taille - aAjouter.taille;
        insertion2(mem.listBlocs, aAjouter, i);
      }
      i++;
      courant = courant->suivant;
    }
  }
  return aAjouter;
}

void liberationMemoire (memoire mem, bloc blocALiberer) {
  Element* courant = mem.listBlocs->premier;
  while (courant != NULL) {
    if (courant->data.debut == blocALiberer.debut && courant->data.taille == blocALiberer.taille) {
      courant->data.drapeau = Libre;
    }
    courant = courant->suivant;
  }

  /* Fusionne avec les bloc libres qui se suivent */
  courant = mem.listBlocs->premier;
  int i = 0;
  while (courant != NULL) {
    if (courant->suivant != NULL) {
      if (courant->suivant->data.drapeau == Libre && courant->data.drapeau == Libre) {
        courant->data.taille = courant->data.taille + courant->suivant->data.taille;
        suppression2(mem.listBlocs, i+1);
      }
      else {
        courant = courant->suivant;
        i++;
      }
    }
    else {
      courant = courant->suivant;
      i++;
    }
  }
}

int main(int argc, char *argv[]) {
  int n;
  if (argc == 1) {
    n = 0;
  }
  else {
    n = atoi(argv[1]);
  }

  memoire m = creerMemoire((int)sizeof(int), 4*n);
  afficherListe(m.listBlocs);
  return 0;
}
