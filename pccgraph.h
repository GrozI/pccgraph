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
    char line;

    unsigned int pred;
    unsigned int dest;
} Arc;
 
struct liste {
 Arc arc;
 struct liste *suiv;};
 typedef struct liste * Liste;



typedef struct {
    double poids;
    char station;
    unsigned int pere;
    int file;
    unsigned int No;
    Liste* arc;
    
} Sommets;

typedef struct {
    unsigned int nX;
    unsigned int nA;
    Sommets* sommets;
}* graphe;



Liste creer_liste(void);
int est_vide(Liste L);
void visualiser_liste(Liste L);
Liste ajout_tete(Arc a,Liste L);
Liste supprimer_tete(Liste L);
Liste ajout_queue(Arc a,Liste L);


graphe nouveau_graphe(unsigned int nX,unsigned int nA);
void visualiser_sommets(Sommets* s);
void affiche_graphe(graphe g);
void detruit_graphe(graphe g);
void graphe_ecrit_nA(graphe g, unsigned int nA);
void graphe_ecrit_nX(graphe g, unsigned int nX);
unsigned int graphe_lit_nA(graphe g);
unsigned int graphe_lit_nX(graphe g);
void graphe_ecrit_poids(graphe g, unsigned int u, double val);
double graphe_lit_poids(graphe g, unsigned int u);
void graphe_ecrit_poids_arc(graphe g, unsigned int u, unsigned int v, double val);
double graphe_lit_poids_arc(graphe g, unsigned int u, unsigned int v);
void graphe_ajoute_arc(graphe g, unsigned int u, unsigned int v, double val);
graphe lit_graphe(char * fichier);
double graphe_pcc(graphe g, unsigned int u, unsigned int v);
#endif /* pccgraph_h */
