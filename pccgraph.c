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
#include "file.h"
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
        printf("%d %d %lf",p->arc.pred,p->arc.dest,p->arc.poids);
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
    p->arc.dest = a.dest;
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
    l->arc.dest = a.dest;
    l->suiv=NULL;
    p->suiv=l;
    return L;
}












graphe nouveau_graphe( int nX, int nA)
{
    int i;
    graphe g;
    Sommets som;
    Liste L;
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
    for(i=0;i<nX;i++)
    {
        som=*((g->sommets)+i);
        L=som.arc;
        L=calloc(1,sizeof(*L));
    }
    return g;
}

void visualiser_sommets(Sommets* s)
{
    Sommets* p;
    p=s;
    printf(" %lf %s %d",p->poids,p->station,p->No);
}



void affiche_graphe(graphe g){
	int i;
	for(i=0;i<(g->nX);i++){
		visualiser_sommets(g->sommets+i);
		}
	for(i=0;i<(g->nX);i++){
		visualiser_liste((g->sommets+i)->arc);
		}
	}



void detruit_graphe(graphe g)
{
    free(g->sommets);
    free(g);
}

void graphe_ecrit_nA(graphe g, int nA)
{
    if (g!=NULL) g->nA=nA;
}
void graphe_ecrit_nX(graphe g, int nX)
{
    if (g!=NULL) g->nX=nX;
}


 int graphe_lit_nA(graphe g)
{
    if (g!=NULL) return g->nA;
    return -1;
}
int graphe_lit_nX(graphe g)
{
    if (g!=NULL) return g->nX;
    return -1;
}

void graphe_ecrit_poids(graphe g, int u, double val)
{
    Sommets* s;
    if (g!=NULL)
    {
        s=g->sommets;
        (s+u)->poids=val;
    }
}
double graphe_lit_poids(graphe g, int u)
{
    Sommets* s;
    if (g!=NULL)
    {
        s=g->sommets;
        return (s+u)->poids;
    }
    return -1;
}


void graphe_ecrit_poids_arc(graphe g, int u, int v, double val)
{
    Sommets* s;
    Liste l,p;
    int i=65535;
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
            else printf("station d'arrivée pas existante v trop grand ecriture");
        }
        else printf("tableau de sommets non existant");
    }
    else printf("graphe non existant");
}


double graphe_lit_poids_arc(graphe g, int u, int v)
{
    Sommets* s;
    Liste l;
    int i=0;
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
                printf("v trop grand lecture");
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


void graphe_ajoute_arc(graphe g, int u,int v, double val)
{
	Arc a;
	a.poids=val;
	a.pred=u;
	a.dest=v;
	
	ajout_tete(a,(g->sommets+u)->arc);	
}


graphe lit_graphe(FILE* fp)//dans le main ouvrir fichier
{
    char mot[511];
    int i=0;
    Sommets som;
    int nX,nA,No,prec,dest;
    double coa,cob,pds;
    fscanf(fp,"%d %d",&nX,&nA);
    graphe g;
    g=nouveau_graphe(nX, nA);
    fgets(mot,511,fp);
    for(i=0;i<nX;i++)
    {
        Liste t;

    	som=*(g->sommets+i);

        t=som.arc;
    	fscanf(fp,"%d %lf %lf %s %s",&No,&coa,&cob,som.line,som.station);
    	som.No=No;
    }
    fgets(mot,511,fp);
    while(fscanf(fp,"%d %d %lf",&prec,&dest,&pds)!=0)
    {
    	graphe_ajoute_arc(g,prec,dest,pds);
    }
    return g;
}

/*double graphe_pcc(graphe g, int u, int v);
{
    int i,j;
    Liste p;
    Sommets s;
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
}*/

double graphe_pcc(graphe g, int u, int v)
{
    int i;
    Liste p;
    File f=creer_file();
    Sommets s;
    enfiler(*(g->sommets),f);
    for(i=0;i<g->nX;i++)
    {
    	((g->sommets)+i)->poids=65535;
        ((g->sommets)+i)->file=0;
    }
    
    (g->sommets+u)->poids=0;
    for(i=0;i<g->nX;i++)
    {
        while(!file_vide(f))
        {
            s=defiler(&f);
            p=(s.arc);
    	    while(!est_vide(p))
    	    {
    	        if(s.poids+p->arc.poids<((g->sommets)+(p->arc.dest))->poids)
    	        {
    	            ((g->sommets)+(p->arc.dest))->poids=s.poids+p->arc.poids;
                    (g->sommets[p->arc.dest]).pere=p->arc.pred;
                    if(g->sommets[p->arc.dest].file==0) enfiler(g->sommets[p->arc.dest],f);
    	        }
                p=p->suiv;
    	    }
        }
    }
    return 1;
}




int main()
{
    FILE* fp=fopen("/users/phelma/phelma2015/grozir/Bureau/graph/metro.txt","r");
    graphe g;
//    g=nouveau_graphe(769,1939);
  //  g->sommets->poids=5;
    g=lit_graphe(fp);
    printf("proof\n");
    return 1;
}
