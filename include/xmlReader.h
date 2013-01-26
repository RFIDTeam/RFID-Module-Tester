#ifndef XML_READER_H
#define XML_READER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/tree.h>
#include <libxml/parser.h>
#include <string.h>

typedef void (*fct_parcours_t)(xmlNodePtr, char*, char*, char*, char*, char*, char*, char*, char*, char*);

void parcours_arbre(xmlNodePtr noeud, fct_parcours_t f, char* type, char* issuer, char* surName, char* givenName, char* number, char* nationality, char* dateOfBirth, char* sex, char* dateOfExpiry);
void afficher_noeud(xmlNodePtr noeud, char* type, char* issuer, char* surName, char* givenName, char* number, char* nationality, char* dateOfBirth, char* sex, char* dateOfExpiry);
void xmlRead(char* xmlFilePath, char* type, char* issuer, char* surName, char* givenName, char* number, char* nationality, char* dateOfBirth, char* sex, char* dateOfExpiry);


#endif
