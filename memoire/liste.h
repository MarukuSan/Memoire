typedef struct Element Element;
struct Element {
    bloc data;
    Element* suivant;
};

typedef struct Liste Liste;
struct Liste {
    Element* premier;
};

Liste* initialisation() {
    Liste *liste = malloc(sizeof(*liste));

    if (liste == NULL) {
        exit(EXIT_FAILURE);
    }

    liste->premier = NULL;

    return liste;
}

/* Renvoyer la taille de la liste 'liste' */
int lenListe(Liste* liste) {
    if (liste->premier == NULL) {
        return 0;
    }
    
    int i = 0;
    Element* courant = liste->premier;
    while (courant != NULL) {
        courant = courant->suivant;
        i++;
    }

    return i;
}

/* Inserer un élément 'nvData' au début de la liste 'liste' */
void insertion(Liste* liste, bloc nvData) {
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)     {
        exit(EXIT_FAILURE);
    }
    nouveau->data = nvData;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

/* Inserer un élément 'nvData' à la position 'index' de la liste 'liste' */
void insertion2(Liste* liste, bloc nvData, int index) {
    if (index > lenListe(liste)) {
        printf("Insertion Impossible : Index out of range\n");
        exit(EXIT_FAILURE);
    }

    if (index == 0) {
        insertion(liste, nvData);
    }
    else {
        /* Création du nouvel élément */
        Element *nouveau = malloc(sizeof(*nouveau));
        if (liste == NULL || nouveau == NULL)     {
            exit(EXIT_FAILURE);
        }
        nouveau->data = nvData;

        int i = 1;
        
        Element* courant = liste->premier;
        while (courant != NULL && i < index) {
            courant = courant->suivant;
            i++;
        }

        /* Insertion du nouvel élément */
        nouveau->suivant = courant->suivant;
        courant->suivant = nouveau;
    }
}

/* Supprimer le premier élément de la liste 'liste' */
void suppression(Liste* liste) {
    if (liste == NULL) {
        exit(EXIT_FAILURE);
    }

    if (liste->premier != NULL) {
        Element* aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

/* Supprimer l'élément au position 'index' dans la liste 'liste' */
void suppression2(Liste* liste, int index) {
    if (index >= lenListe(liste)) {
        printf("Suppression Impossible : Index out of range\n");
        exit(EXIT_FAILURE);
    }

    if (index == 0) {
        suppression(liste);
    }
    else {
        if (liste == NULL) {
            exit(EXIT_FAILURE);
        }

        int i = 1;
        Element* courant = liste->premier;
        Element* aSupprimer;

        while (courant != NULL && i < index) {
            courant = courant->suivant;
            i++;
        }

        aSupprimer = courant->suivant;
        courant->suivant = aSupprimer->suivant;
        free(aSupprimer);        
    }
}

/* Afficher la liste 'liste' */
void afficherListe(Liste *liste) {
    if (liste == NULL) {
        exit(EXIT_FAILURE);
    }

    Element* actuel = liste->premier;

    while (actuel != NULL) {
        printf("(%d, %d, %d) -> ", actuel->data.debut, actuel->data.taille, actuel->data.drapeau);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}