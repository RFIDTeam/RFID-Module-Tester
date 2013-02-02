#ifndef CALLBACK_H
#define CALLBACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>


void Readme (GtkWidget *wid, gpointer user_data);
void fct_ouvrir(GtkWidget *, gpointer);
static void open_file (const gchar *file_name, GtkTextView *zone_texte);
void showPhoto (GtkWidget *wid, gpointer data);
void copierMRZ (GtkWidget *, gpointer);
void lancer(GtkWidget *, gpointer);
int readPassport (char* MRZ, char* FileName, char* CommandLine, FILE* sortie, char* tampon);
void moveXmlToDataBase (char* MvXmlCommandLine, char* FileName, FILE* sortie, char* tampon);
void moveJp2ToDataBase (char* MvJpgCommandLine, char* FileName, FILE* sortie, char* tampon);

#endif
