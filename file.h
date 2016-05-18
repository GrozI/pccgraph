#ifndef _FILE
#define _FILE

#include"pccgraph.h"

typedef struct cellule { Sommets som ; struct cellule* suiv; } maillon ;

typedef maillon* File;

File creer_file(void);

int file_vide(File f);

File enfiler(Sommets s, File f);
	
Sommets defiler(File *f);

#endif














































