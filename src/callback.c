#include "callback.h"
#include "xmlReader.h"

#define DEFAULT_FILE "main.c"


static void open_file (const gchar *, GtkTextView *);



void fct_ouvrir(GtkWidget *wid, gpointer user_data)
{
    GtkWidget *selectionneur = NULL;

    selectionneur = gtk_file_chooser_dialog_new ("Quel fichier souhaitez vous afficher?", NULL,
                                                 GTK_FILE_CHOOSER_ACTION_OPEN,
                                                 GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);

    if (gtk_dialog_run (GTK_DIALOG (selectionneur)) == GTK_RESPONSE_ACCEPT){
        gchar *file_name = NULL;

        file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (selectionneur));
        open_file (file_name, GTK_TEXT_VIEW (user_data));
        g_free (file_name), file_name = NULL;
    }
    gtk_widget_destroy (selectionneur);
}


void fct_ouvrir2(GtkWidget *wid, gpointer user_data)
{
    GtkWidget *selectionneur = NULL;

    selectionneur = gtk_file_chooser_dialog_new ("Quel fichier souhaitez vous ouvrir?", NULL,
                                                 GTK_FILE_CHOOSER_ACTION_OPEN,
                                                 GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);

    if (gtk_dialog_run (GTK_DIALOG (selectionneur)) == GTK_RESPONSE_ACCEPT){
        gchar *file_name = NULL;
        char tampon[UCHAR_MAX];
        FILE *sortie;
        char cmd[1000];

        file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (selectionneur));
        sprintf (cmd, "pwd ; cd %s ; pwd", file_name);

        if((sortie=popen(cmd, "r")) == NULL){
            fprintf (stderr, "erreur");
        }
        while (fgets (tampon, sizeof tampon, sortie) != NULL){
            fputs (tampon, stdout);
        }

        fclose (sortie);

        g_free (file_name), file_name = NULL;
    }
    gtk_widget_destroy (selectionneur);
}


void readPassport (char* MRZ, char* FileName, char* CommandLine, FILE* sortie, char* tampon)
{
    //Edition of the main command line
    strcat(CommandLine,"./wzmrtd-tool.static -r \"#1\" -z '");
    strcat(CommandLine,MRZ);
    strcat(CommandLine,"\r\n");
    strcat(CommandLine,MRZ);
    strcat(CommandLine,"' -f ");
    strcat(CommandLine, FileName);
    strcat(CommandLine,".xml -v -xsi -y");

    if((sortie=popen(CommandLine, "r")) == NULL){
        fprintf (stderr, "erreur");
    }

    while (fgets (tampon, sizeof tampon, sortie) != NULL){
        fputs (tampon, stdout);
    }

    fclose (sortie);
}


void moveXmlToDataBase (char* MvXmlCommandLine, char* FileName, FILE* sortie, char* tampon)
{
    //Edition of the xml move command line
    strcat(MvXmlCommandLine,"mv ");
    strcat(MvXmlCommandLine, FileName);
    strcat(MvXmlCommandLine, ".xml ./../DataBase");

    if((sortie=popen(MvXmlCommandLine, "r")) == NULL){
        fprintf (stderr, "erreur");
    }

    while (fgets (tampon, sizeof tampon, sortie) != NULL){
        fputs (tampon, stdout);
    }

    fclose (sortie);
}


void moveJp2ToDataBase (char* MvJpgCommandLine, char* FileName, FILE* sortie, char* tampon)
{
    //Edition of the jpg move command line
    strcat(MvJpgCommandLine,"mv ");
    strcat(MvJpgCommandLine, FileName);
    strcat(MvJpgCommandLine, "_fac_0.jp2 ./../DataBase");

    if((sortie=popen(MvJpgCommandLine, "r")) == NULL){
        fprintf (stderr, "erreur");
    }

    while (fgets (tampon, sizeof tampon, sortie) != NULL){
        fputs (tampon, stdout);
    }

    fclose (sortie);
}


void lancer (GtkWidget *wid, gpointer win)
{

    char tampon[UCHAR_MAX];
    FILE* sortie;
    FILE* sortie2;
    FILE* sortie3;
    FILE* sortie4;
    FILE* sortie5;
    char CommandLine [300] = {0};
    char MRZ[44]={0};
    char FileName[44]={0};
    char MvXmlCommandLine[65]={0};
    char MvJpgCommandLine[71]={0};
    char xmlDirectory[66]={0};
    char** data1 = NULL;
    char** data2 = NULL;
    int i;
    FILE* mrzFile;

    // Ajouter fonction pour rentrer la MRZ <---------------------------------
    //strcat(MRZ, "0123456784UTO8001014F2501017<<<<<<<<<<<<<<06");
    //strcat(MRZ, "09PI870308FRA9011090M1909100<<<<<<<<<<<<<<04");
    strcat(MRZ, "EV02120860MAR8807113F1511114BE812755<<<<<<78");


    if (MRZ == NULL){
        fprintf (stderr, "Erreur, MRZ non-valide");
    }

    // Edition of the file name
    for (i=0 ; i < 28 ; i++){
        FileName[i] = MRZ[i] ;
        if (MRZ[i] == "<" ){
            FileName[i] = "_";
        }
    }

    // Path to the supposed xml file in the DataBase
    strcat(xmlDirectory, "./../DataBase/");
    strcat(xmlDirectory, FileName);
    strcat(xmlDirectory, ".xml");
    printf("%s\n", xmlDirectory);

    // Test if passport already in database
    if (fopen(xmlDirectory, "r")!= NULL){
		printf("\n\n\n --------------------------------\nPassport in DataBase, data check in progress ...\n");
        readPassport (MRZ, "temp", CommandLine, sortie, tampon);
        // Read xml files
        data1 = xmlRead("temp.xml");
        data2 = xmlRead(xmlDirectory);
        //Comparison
        if ((strcmp (data1[0], data2[0]) == 0) && (strcmp (data1[1], data2[1]) == 0)
                                               && (strcmp (data1[2], data2[2]) == 0)
                                               && (strcmp (data1[3], data2[3]) == 0)
                                               && (strcmp (data1[4], data2[4]) == 0)
                                               && (strcmp (data1[5], data2[5]) == 0)
                                               && (strcmp (data1[6], data2[6]) == 0)
                                               && (strcmp (data1[7], data2[7]) == 0)
                                               && (strcmp (data1[8], data2[8]) == 0))
                                               {
                                                   printf("\n----> Passport data matched, operational RFID reader <----\n");
                                               }
                                               sortie4=popen("rm temp.xml", "r");
                                               sortie5=popen("rm temp_fac_0.jp2", "r");
	}
	else {
		printf("\n\n\n --------------------------------\nNew passport detected, registration in database in progress ...\n");
        readPassport (MRZ, FileName, CommandLine, sortie, tampon);
        moveXmlToDataBase (MvXmlCommandLine, FileName, sortie2, tampon);
        moveJp2ToDataBase (MvJpgCommandLine, FileName, sortie3, tampon);
        data1 = xmlRead(xmlDirectory);
        printf("\n----> Passport added to data base <----\n");
        // Adding the MRZ to the MRZ.txt file
        mrzFile = fopen("./../MRZ.txt","a");
        fprintf(mrzFile,"%s\n",MRZ);
        fclose(mrzFile);
	}
    printf("\nPassport data :\n");
    printf("Type : %s\n", data1[0]);
    printf("Issuer : %s\n", data1[1]);
    printf("Surname : %s\n", data1[2]);
    printf("Given name : %s\n", data1[3]);
    printf("Number : %s\n", data1[4]);
    printf("Nationality : %s\n", data1[5]);
    printf("Date of birth (yymmdd): %s\n", data1[6]);
    printf("Sex : %s\n", data1[7]);
    printf("Date of expiry (yymmdd): %s\n", data1[8]);

    GtkWidget *dialog = NULL;
    dialog = gtk_message_dialog_new (GTK_WINDOW (win),
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK, "Passport reading ended");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}


static void open_file (const gchar *file_name, GtkTextView *zone_texte)
{
    g_return_if_fail (file_name && zone_texte);
    {
        gchar *contents = NULL;

        if (g_file_get_contents (file_name, &contents, NULL, NULL)) {
            /* Copie de contents dans le GtkTextView */

            gchar *utf8 = NULL;
            GtkTextIter iter;
            GtkTextBuffer *buffer = NULL;

            buffer = gtk_text_view_get_buffer (zone_texte);
            gtk_text_buffer_get_iter_at_line (buffer, &iter, 0);
            utf8 = g_locale_to_utf8 (contents, -1, NULL, NULL, NULL);
            g_free (contents), contents = NULL;
            gtk_text_buffer_insert (buffer, &iter, utf8, -1);
            g_free (utf8), utf8 = NULL;
        }
        else {
            printf ("Impossible d'ouvrir le fichier %s\n", file_name);
        }
    }
}
