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

//  (void) *wid;
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

//  (void) *wid;
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
    FILE *sortie;
    FILE *sortie2;
    FILE *sortie3;
    char CommandLine [300] = {0};
    char MRZ[44]={0};
    char FileName[34]={0};
    char MvXmlCommandLine[51]={0};
    char MvJpgCommandLine[57]={0};
    char xmlDirectory[52]={0};
    char* type = NULL;
    char* issuer = NULL;
    char* surName = NULL;
    char* givenName = NULL;
    char* number = NULL;
    char* nationality = NULL;
    char* dateOfBirth = NULL;
    char* sex = NULL;
    char* dateOfExpiry = NULL;
    char* ttype = NULL;
    char* tissuer = NULL;
    char* tsurName = NULL;
    char* tgivenName = NULL;
    char* tnumber = NULL;
    char* tnationality = NULL;
    char* tdateOfBirth = NULL;
    char* tsex = NULL;
    char* tdateOfExpiry = NULL;
    int i;

    // Ajouter fonction pour rentrer la MRZ

    //strcat(MRZ, "0123456784UTO8001014F2501017<<<<<<<<<<<<<<06");
    strcat(MRZ, "09PI870308FRA9011090M1909100<<<<<<<<<<<<<<04");

    if (MRZ == NULL){
        fprintf (stderr, "Erreur, MRZ non-valide");
    }

    // Edition of the file name
    for (i=0 ; i < 28 ; i++){
        FileName[i] = MRZ[i] ;
    }
    FileName[28] = MRZ[42];
    FileName[29] = MRZ[43];

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
        xmlRead("temp.xml", type, issuer, surName, givenName, number, nationality, dateOfBirth, sex, dateOfExpiry);
        xmlRead(xmlDirectory, ttype, tissuer, tsurName, tgivenName, tnumber, tnationality, tdateOfBirth, tsex, tdateOfExpiry);
        //Comparison
        if ((strcmp (type, ttype) == 0) && (strcmp (issuer, tissuer) == 0)
                                        && (strcmp (surName, tsurName) == 0)
                                        && (strcmp (givenName, tgivenName) == 0)
                                        && (strcmp (number, tnumber) == 0)
                                        && (strcmp (nationality, tnationality) == 0)
                                        && (strcmp (dateOfBirth, tdateOfBirth) == 0)
                                        && (strcmp (sex, tsex) == 0)
                                        && (strcmp (dateOfExpiry, tdateOfExpiry) == 0))
                                        {
                                            printf("\n----> Passport data matched, operational RFID reader <----\n");
                                        }
	}
	else {
		printf("\n\n\n --------------------------------\nNew passport detected, registration in database in progress ...\n");
        readPassport (MRZ, FileName, CommandLine, sortie, tampon);
        moveXmlToDataBase (MvXmlCommandLine, FileName, sortie2, tampon);
        moveJp2ToDataBase (MvJpgCommandLine, FileName, sortie3, tampon);
        xmlRead(xmlDirectory, type, issuer, surName, givenName, number, nationality, dateOfBirth, sex, dateOfExpiry);
        printf("\n----> Passport added to data base <----\n");
	}

    printf("\nPassport data :\n");
    printf("Type : %s\n", type);
    printf("Issuer : %s\n", issuer);
    printf("Surname : %s\n", surName);
    printf("Given name : %s\n", givenName);
    printf("Number : %s\n", number);
    printf("Nationality : %s\n", nationality);
    printf("Date of birth : %s\n", dateOfBirth);
    printf("Sex : %s\n", sex);
    printf("Date of expiry : %s\n", dateOfExpiry);


    GtkWidget *dialog = NULL;
    dialog = gtk_message_dialog_new (GTK_WINDOW (win),
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK, "AAAAaaaaaaaaaaaaaah!");
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
