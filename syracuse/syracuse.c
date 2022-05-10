#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 100
#define NB_THREAD 10

//Tableau qui stocke les valeurs de la fonction de syracuse
int *syracuse;

/*Exemple de structure contenant les arguments passes a chaque thread
 * Chaque thread devrai calculer syracuse de start jusqu'à end
 * */
typedef struct syracuse_args {
    int start;
    int end;
} syracuse_args;

/* Calcule la suite de Syracuse de start en n */
int suite_syracuse(int start, int n) {
    int a = start;
    
    for (int i=1; i<=n; i++) {
        if (a%2 == 0) {
            a = a/2;
        }
        else {
            a = (3*a) + 1;
        }
    }

    return a;
}

/* Calcule la durée du vol d'un entier a */
int duree_vol(int a) {
    int nbre = a;
    int duree = 0;
    while (a != 1) {
        if (syracuse[a-1] != -1 && a-1<SIZE) {
            printf("J'ai utilise le duree de vol de %d pour %d a l'etape %d\n", a, nbre, duree);
            return duree + syracuse[a-1];
        }
        else if (a%2 == 0) {
            a = a/2;
        }
        else {
            a = (3*a) + 1;
        }
        duree++;
    }
    return duree;
}

/* Partitionne le tableau tab en n */
syracuse_args* part_tab(int taille, int n) {
    syracuse_args* t = malloc(sizeof(syracuse_args)*n);
    int s = 1;
    int part = taille/n;

    if ((taille/(float)n) - part > 0.5) {
        part++;
    }
    
    for (int i=0; i<n-1; i++) {
        t[i].start = s;
        t[i].end = (part*(i+1));
        s = s + part;
    }

    t[n-1].start = s;
    t[n-1].end = taille;

    return t;
}

/* Affiche les attributs d'un syracuse_args */
void affiche_syracuse_args(syracuse_args a) {
    printf("start : %d  |  end : %d\n", a.start, a.end);
}

/* Affiche un tableau de int*/ 
void affiche_tab(int* tab, int taille) {
    for (int i=0; i<taille; i++) {
        printf("%d | ", tab[i]);
    }
    printf("\n");
}

/* Affiche un tableau de syracuse_args*/ 
void affiche_tab_syracuse_args(syracuse_args* tab, int taille) {
    for (int i=0; i<taille; i++) {
        affiche_syracuse_args(tab[i]);
    }
    printf("\n");
}

void inter_duree_vol(syracuse_args* a) {
    int s = a->start -1;
    int e = a->end -1;

    for (int i=s; i<=e; i++) {
        syracuse[i] = duree_vol(i+1);
    }
}

void *vol_d(void* arg){
    inter_duree_vol(arg);
    pthread_exit (NULL) ;
}

int main()
{
    syracuse = (int *) malloc((SIZE+1) * sizeof(int));

    /* Initialisation du tableau syracuse */
    for (int i=0; i<SIZE; i++) {
        syracuse[i] = -1;
    }

    /* Affiche les valeurs stockées dans syracuse */
    /* for (int i=0; i<100; i++) {
        printf("%d : %d\n", i+1, syracuse[i]);
    } */

    /* for (int i=0; i<SIZE; i++) {
        tab[i] = duree_vol(tab[i]);
    }
    affiche_tab(tab, SIZE); */


    /* Calcule les parts (intervalles) pour chaque thread */
    syracuse_args* t = part_tab(SIZE, NB_THREAD);
    affiche_tab_syracuse_args(t, NB_THREAD);

    /* Création d'un tableau allant contenir les threads qu'on va créer */
    pthread_t* tab_thread = malloc(sizeof(pthread_t)*NB_THREAD);

    /* Création de threads dans chaque case de tab_thread */
    for (int i=0; i<NB_THREAD; i++) {
        pthread_create(&tab_thread[i], NULL, vol_d, &t[i]);
    }
    
    /* Attente que chaque thread se termine */
    for (int i=0; i<NB_THREAD; i++) {
        pthread_join(tab_thread[i],NULL);
    }

    /* Affiche les valeurs stockées dans syracuse */
    for (int i=0; i<SIZE; i++) {
        printf("%d : %d\n", i+1, syracuse[i]);
    }


    free(tab_thread);
    free(syracuse);
    return 0;
}
