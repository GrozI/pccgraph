#include "file.h"
#include "pccgraph.h"
File creer_file(void){
	return NULL ;}

int file_vide(File f){
	return !f;}



File enfiler(Sommets s, File f)
{
	File d=calloc(1,sizeof(*d));
	s.file=1;
	d->som=s;
	if(file_vide(f)) d->suiv=d;
	else{
		d->suiv=f->suiv;
		f->suiv=d;}
	return d ;
}
	
Sommets defiler(File *f)
{ 
	Sommets s ;
	File g=*f;
	if((*f)->suiv==*f){
		s=(*f)->som;
		free(f);
		*f=NULL;
		return s ;}
	else{
		g=g->suiv;
		s=g->som;
		(*f)->suiv=g->suiv;
		free(g);
		return s ;}
}

