//
//  pccgraph.c
//  
//
//  Created by I. Groz on 14/04/2016.
//
//

#include <stdio.h>
#include <string.h>
#include "pccgraph.h"

Liste creer_liste(void)
{
    return NULL;
}
int est_vide(Liste L)
{
    return !L;
}
void visualiser_liste(Liste L)
{
    Liste p;
    p=L;
    while(!est_vide(p))
    {
        printf("%u %u %lf %s",p->arc.pred,p->arc.dest,p->arc.poids,p->arc.line);
        p=p->suiv;
    }
    
}

Liste ajout_tete(Arc a,Liste L)
{
    Liste p;
    p=calloc(1,sizeof(*p));
    if(p==NULL) return NULL;
    p->arc.poids = a.poids;
    p->arc.pred = a.pred;
    p->arc.suiv = a.suiv;
    p->suiv=L;
    return p;
}
Liste supprimer_tete(Liste L)
{
    if(!est_vide(L))
    {
        Liste p;
        p=L->suiv;
        free(L);
        return(p);
    }
    return NULL;
}

Liste ajout_queue(Arc a,Liste L)
{
    Liste p,l;
    p=L;
    if(est_vide(L)) return ajout_tete(a,L);
    while(!est_vide(p->suiv))
    {
        p=p->suiv;
    }
    l=calloc(1,sizeof(*l));
    l->arc.poids = a.poids;
    l->arc.pred = a.pred;
    l->arc.suiv = a.suiv;
    l->suiv=NULL;
    p->suiv=l;
    return L;
}












graphe nouveau_graphe(unsigned int nX,unsigned int nA)
{
    graphe g;
    g=calloc(1,sizeof(*g));
    if(g==NULL)
    {
        printf("erreur d'allocation memoire graphe\n");
        return NULL;
    }
    g->nX=nX;
    g->nA=nA;
    g->sommets=calloc(nX,sizeof(Sommets));
    if(g->sommets==NULL)
    {
        printf("erreur d'allocation memoire tableau sommets\n");
        return NULL;
    }
    return g;
}

void visualiser_sommets(Sommets* s)
{
    Sommets* p;
    p=s;
    printf(" %lf %s %u",p->poids,p->station,p->No);
}



void affiche_graphe(graphe g){
	int i;
	for(i=0;i<(g->nX);i++){
		visualiser_sommets(g->sommets+i);
		}
	for(i=0;i<(g->nX);i++){
		visualiser_liste(g->(sommets+i)->arc);
		}
	}



void detruit_graphe(graphe g)
{
    free(g->sommets);
    free(g);
}

void graphe_ecrit_nA(graphe g, unsigned int nA)
{
    if (g!=NULL) g->nA=nA;
}
void graphe_ecrit_nX(graphe g, unsigned int nX)
{
    if (g!=NULL) g->nX=nX;
}


unsigned int graphe_lit_nA(graphe g)
{
    if (g!=NULL) return g->nA;
}
unsigned int graphe_lit_nX(graphe g)
{
    if (g!=NULL) return g->nX;
}

void graphe_ecrit_poids(graphe g, unsigned int u, double val)
{
    Sommets* s;
    if (g!=NULL)
    {
        s=g->sommets;
        (s+u)->poids=val;
    }
}
double graphe_lit_poids(graphe g, unsigned int u)
{
    Sommets* s;
    if (g!=NULL)
    {
        s=g->sommets;
        return (s+u)->poids;
    }
}

void graphe_ecrit_poids_arc(graphe g, unsigned int u, unsigned int v, double val)
{
    Sommets* s;
    Liste l,p;
    unsigned int i=222222222222;
    if(g!=NULL)
    {
        s=g->sommets;
        if(s!=NULL)
        {
            l=(s+u)->arc;
            while(i!=v && l->suiv!=NULL)
            {
	         p=p->suiv;
                 i=(l->arc).pred;
            }
            if(i==v) (l->arc).poids=val;
            else printf("station d'arrivée pas existante v trop grand ecriture")
        }
        else printf("tableau de sommets non existant");
    }
    else printf("graphe non existant");
}
double graphe_lit_poids_arc(graphe g, unsigned int u, unsigned int v)
{
    Sommets* s;
    Liste l;
    unsigned int i=0;
    if(g!=NULL)
    {
        s=g->sommets;
        if(s!=NULL)
        {
            l=(s+u)->arc;
            while(i!=v && l->suiv!=NULL)
            {
                 i++;
                 l=l->suiv;
            }
            if(i==v) return (l->arc).poids;
            else 
            {
                printf("v trop grand lecture")
                return -1;
            }
        }
        else 
        {
             printf("tableau de sommets non existant");
             return -1;
        }
    }
    else
    {   
        printf("graphe non existant ou vide");
        return -1;
    }
}
void graphe_ajoute_arc(graphe g, unsigned int u, unsigned int v, double val)
{
	Liste l;
	Arc a;
	a.poids=val;
	a.pred=u;
	a.dest=v;
		
	l->arc=a;
	
	ajout_queue(a,g->(sommets+u)->arc);	
}

graphe lit_graphe(char * fichier);
{
    unsigned char* mot;
    int i=0;
    Sommets som;
    Arc a;
    Liste l;
    unsigned int nX,nA,No,prec,dest;
    double coa,cob,pds;
    char* line,name;
    fscanf(fp,"%u %u",&nX,&nA);
    graphe g;
    g=nouveau_graphe(nX, nA);
    fgets(mot,511,fp);
    for(i=0;i<nX;i++)
    {
    	som=(g->(sommets+i));
    	fscanf(fp,"%u %lf %lf %s %s",&No,&coa,&cob,som.line,som.name);
    	som.No=No;
    }
    fgets(fp);
    while(fscanf(fp,"%u %u %lf",&prec,&dest,&pds)!=0)
    {
    	graphe_ajoute_arc(g,prec,dest,pds);
    }
}

double graphe_pcc(graphe g, unsigned int u, unsigned int v);
{
    int i,j;
    Liste p;
    Sommet s;
    for(i=0;i<g->nX;i++)
    {
    	((g->sommets)+i)->poids=65535;
    }
    (g->sommets)->poids=0;
    for(i=0;i<g->nX;i++)
    {
    	
    }
    	    p=s.arc;
    	    while(!est_vide(p))
    	    {
    	        if(s->poids+p->poids<((g->sommets)+(p->dest))->poids)
    	        {
    	            ((g->sommets)+(p->dest))->poids=s->poids+p->poids;
    	        }
                p=p->suiv;
    	    }
    	}
    }
    for(i=0;i<g->nX;i++)
    {
    	s=(g->sommets)+j;
    	p=s.arc;
        while(!est_vide(p))
	{
            if(s->poids+p->poids<((g->sommets)+(p->dest))->poids)
   	        {
    	            printf("circuit négatif dans le graphe, chemin impossible");
    	            return 0;
    	        }
            p=p->suiv;
    	}
    }
    return 1;
}
