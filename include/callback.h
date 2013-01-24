#include <stdlib.h>
#include <gtk/gtk.h>

void fct_ouvrir(GtkWidget *, gpointer);
void fct_ouvrir2(GtkWidget *, gpointer);
void lancer(GtkWidget *, gpointer);
void readPassport (char* MRZ, char* FileName, char* CommandLine, FILE* sortie, char* tampon);
void moveXmlToDataBase (char* MvXmlCommandLine, char* FileName, FILE* sortie, char* tampon);
void moveJp2ToDataBase (char* MvJpgCommandLine, char* FileName, FILE* sortie, char* tampon);
