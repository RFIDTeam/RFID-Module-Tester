#ifndef CALLBACK_H
#define CALLBACK_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/tree.h>
#include <libxml/parser.h>
#include <string.h>

char** parcours_arbre(xmlNodePtr noeud);
char** xmlRead(char* xmlFilePath);
void fct_ouvrir(GtkWidget *, gpointer);
void fct_ouvrir2(GtkWidget *, gpointer);
void lancer(GtkWidget *, gpointer);
void readPassport (char* MRZ, char* FileName, char* CommandLine, FILE* sortie, char* tampon);
void moveXmlToDataBase (char* MvXmlCommandLine, char* FileName, FILE* sortie, char* tampon);
void moveJp2ToDataBase (char* MvJpgCommandLine, char* FileName, FILE* sortie, char* tampon);

#endif
