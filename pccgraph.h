//
//  pccgraph.h
//  
//
//  Created by I. Groz on 14/04/2016.
//
//

#ifndef pccgraph_h
#define pccgraph_h

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    double poids;
    int pred;
    int dest;
} Arc;
 
struct liste {
 Arc arc;
 struct liste *suiv;};
 typedef struct liste * Liste;



typedef struct {
    double poids;
    char station[511];
    int pere;
    char line[511];
    int file;
    int No;
    Liste arc;
} Sommets;

typedef struct {
    int nX;
    int nA;
    Sommets* sommets;
}* graphe;



Liste creer_liste(void);
int est_vide(Liste L);
void visualiser_liste(Liste L);
Liste ajout_tete(Arc a,Liste L);
Liste supprimer_tete(Liste L);
Liste ajout_queue(Arc a,Liste L);


graphe nouveau_graphe( int nX, int nA);
void visualiser_sommets(Sommets s);
void affiche_graphe(graphe g);
void detruit_graphe(graphe g);
void graphe_ecrit_nA(graphe g, int nA);
void graphe_ecrit_nX(graphe g, int nX);
int graphe_lit_nA(graphe g);
int graphe_lit_nX(graphe g);
void graphe_ecrit_poids(graphe g, int u, double val);
double graphe_lit_poids(graphe g, int u);
void graphe_ecrit_poids_arc(graphe g, int u, int v, double val);
double graphe_lit_poids_arc(graphe g, int u, int v);
void graphe_ajoute_arc(graphe g, int u, int v, double val);
graphe lit_graphe(FILE* fp);
double graphe_pcc(graphe g, int u, int v);
#endif /* pccgraph_h */
