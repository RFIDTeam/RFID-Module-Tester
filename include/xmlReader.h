#ifndef XML_READER_H
#define XML_READER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/tree.h>
#include <libxml/parser.h>
#include <string.h>

typedef void (*fct_parcours_t)(xmlNodePtr);

void parcours_arbre(xmlNodePtr noeud, fct_parcours_t f);
void afficher_noeud(xmlNodePtr noeud);
char** xmlRead(char* xmlFilePath);


#endif
