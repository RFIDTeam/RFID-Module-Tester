#include "callback.h"
#include "xmlReader.h"
#include <string.h>


#define DEFAULT_FILE "main.c"

static char MRZcopiee[44]={0};
static char MRZcopiee2[44]={0};

static void open_file (const gchar *, GtkTextView *);

void copierMRZ (GtkWidget *wid, gpointer data)
{
    const gchar * sText;
    /* Recuperation du texte contenu dans le champMRZ */
    sText = gtk_entry_get_text(GTK_ENTRY(data));

    /* Modification de la constante MRZ_2 */
    strcpy (MRZcopiee, sText);
//    printf("MRZcopiee = %s\n",MRZcopiee);
}

void showPhoto (GtkWidget *wid, gpointer data)
{
    char imgPath[500]={0};
    GList *pList;
    GtkWidget *tempImg=NULL;
/*
    wait (60);
    strcpy(imgPath, "./../DataBase/");
    strcat(imgPath, MRZcopiee2);
    strcat(imgPath, "_fac_0.jp2");
    printf("img = %s\n",imgPath);
*/
    strcpy(imgPath, "temp_fac_0.jp2");
    pList = gtk_container_get_children (GTK_CONTAINER((GtkWidget*)data));
    tempImg = GTK_WIDGET(pList->data);
    gtk_image_set_from_file (GTK_IMAGE(tempImg), imgPath);
}

void fct_ouvrir(GtkWidget *wid, gpointer user_data)
{
    /*
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
    */
    open_file ("./../MRZ.txt", GTK_TEXT_VIEW (user_data));
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

void Readme (GtkWidget *wid, gpointer user_data)
{
    GtkWidget *win2 = NULL;
    GtkWidget *scrolled_win = NULL;
    GtkWidget *zone_texte = NULL;
    GtkWidget *vbox =NULL;
//    GtkWidget *label = NULL;

    win2 = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée la fenetre
    gtk_container_set_border_width (GTK_CONTAINER (win2), 10); //définit la taille de la bordure de la fenetre
    gtk_window_set_default_size(GTK_WINDOW(win2),500,600); // dimensionne la fenetre
    gtk_window_set_title (GTK_WINDOW (win2), "CheckMyPassport"); //donne un titre à la fenetre
    gtk_window_set_position(GTK_WINDOW(win2), GTK_WIN_POS_CENTER); //centre la fenetre à son ouverture
    g_signal_connect (win2, "destroy", gtk_quit_add_destroy, NULL); // Connecte le bouton de fermeture de la fenetre à la fermeture de la fenetre

        /* Creation of the text zone */
    zone_texte = gtk_text_view_new();
    scrolled_win = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    vbox= gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER(win2), vbox);
    gtk_box_pack_start (GTK_BOX(vbox), scrolled_win, TRUE, TRUE,0);
    gtk_container_add (GTK_CONTAINER(scrolled_win), zone_texte);
    open_file("./../README.txt", zone_texte);

    gtk_widget_show_all(win2);

}

int readPassport (char* MRZ, char* FileName, char* CommandLine, FILE* sortie, char* tampon)
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
        return 0;
    }

    while (fgets (tampon, sizeof tampon, sortie) != NULL){
        fputs (tampon, stdout);
    }

    fclose (sortie);
    return 1;
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


void lancer (GtkWidget *wid, gpointer data)
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
    const gchar * sText;
    GList *pList;
    GtkWidget *tempLabel;
    const gchar * sText2;
    GtkWidget *tempLabel2;

    // Ajouter fonction pour rentrer la MRZ <---------------------------------
    //strcat(MRZ, "0123456784UTO8001014F2501017<<<<<<<<<<<<<<06");
    //strcat(MRZ, "09PI870308FRA9011090M1909100<<<<<<<<<<<<<<04");
    strcpy(MRZ, MRZcopiee);

    if ((MRZ == NULL) || (strlen(MRZ) != 44)){
        fprintf (stderr, "Erreur, MRZ non-valide");
        /* Creation of an error pop up window */
           GtkWidget *popup = NULL; //on va creer une fenetre
           GtkWidget *dialog = NULL; //et une boite de dialogue a l'intérieur de cette dernière
            popup = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée une nouvelle fenetre appelée popup
            gtk_window_set_title (GTK_WINDOW (popup), "Passport checked"); //titre de la fenetre
            /* Insertion de la boite de dialogue dans la fenetre popup */
            dialog = gtk_message_dialog_new (GTK_WINDOW (popup),
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_OTHER,
                                             GTK_BUTTONS_OK, "Passport MRZ wrong");
            gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
            gtk_dialog_run (GTK_DIALOG (dialog));
            gtk_widget_destroy (dialog);
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

    // Test if supposed xml file already in database
    if (fopen(xmlDirectory, "r")!= NULL){
		printf("\n\n --------------------------------\nPassport in DataBase, data check in progress ...\n");
        // Test if readpassport doesn't work
        if ((readPassport (MRZ, "temp", CommandLine, sortie, tampon)) == 0)
        {
            /* Creation of an error pop up window */
           GtkWidget *popup = NULL; //on va creer une fenetre
           GtkWidget *dialog = NULL; //et une boite de dialogue a l'intérieur de cette dernière
            popup = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée une nouvelle fenetre appelée popup
            gtk_window_set_title (GTK_WINDOW (popup), "Passport checked"); //titre de la fenetre
            /* Insertion de la boite de dialogue dans la fenetre popup */
            dialog = gtk_message_dialog_new (GTK_WINDOW (popup),
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_OTHER,
                                             GTK_BUTTONS_OK, "Error : can't read passport");
            gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
            gtk_dialog_run (GTK_DIALOG (dialog));
            gtk_widget_destroy (dialog);
        };
        // Read xml files
        if ((data1 = xmlRead("temp.xml")) == NULL)
        {
            /* Creation of an error pop up window */
           GtkWidget *popup = NULL; //on va creer une fenetre
           GtkWidget *dialog = NULL; //et une boite de dialogue a l'intérieur de cette dernière
            popup = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée une nouvelle fenetre appelée popup
            gtk_window_set_title (GTK_WINDOW (popup), "Passport checked"); //titre de la fenetre
            /* Insertion de la boite de dialogue dans la fenetre popup */
            dialog = gtk_message_dialog_new (GTK_WINDOW (popup),
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_OTHER,
                                             GTK_BUTTONS_OK, "Passport MRZ wrong");
            gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
            gtk_dialog_run (GTK_DIALOG (dialog));
            gtk_widget_destroy (dialog);
        }
        if ((data2 = xmlRead(xmlDirectory))==NULL)
        {
            /* Creation of an error pop up window */
           GtkWidget *popup = NULL; //on va creer une fenetre
           GtkWidget *dialog = NULL; //et une boite de dialogue a l'intérieur de cette dernière
            popup = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée une nouvelle fenetre appelée popup
            gtk_window_set_title (GTK_WINDOW (popup), "Passport checked"); //titre de la fenetre
            /* Insertion de la boite de dialogue dans la fenetre popup */
            dialog = gtk_message_dialog_new (GTK_WINDOW (popup),
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_OTHER,
                                             GTK_BUTTONS_OK, "Passport not in database");
            gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
            gtk_dialog_run (GTK_DIALOG (dialog));
            gtk_widget_destroy (dialog);
        }
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
           /* Creation of a success pop up window */
           GtkWidget *popup = NULL; //on va creer une fenetre
           GtkWidget *dialog = NULL; //et une boite de dialogue a l'intérieur de cette dernière
            popup = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée une nouvelle fenetre appelée popup
            gtk_window_set_title (GTK_WINDOW (popup), "Passport checked"); //titre de la fenetre
            /* Insertion de la boite de dialogue dans la fenetre popup */
            dialog = gtk_message_dialog_new (GTK_WINDOW (popup),
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_OTHER,
                                             GTK_BUTTONS_OK, "Passport data MATCHED !");
            gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
            gtk_dialog_run (GTK_DIALOG (dialog));
            gtk_widget_destroy (dialog);
       }


    else {
        printf("\n----> Error : passport data not matched, non-operational RFID reader <----\n");
            /* Creation of an error pop up window */
    GtkWidget *popup = NULL; //on va creer une fenetre
    GtkWidget *dialog = NULL; //et une boite de dialogue a l'intérieur de cette dernière
    popup = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée une nouvelle fenetre appelée popup
    gtk_window_set_title (GTK_WINDOW (popup), "Passport checked"); //titre de la fenetre
    /* Insertion de la boite de dialogue dans la fenetre popup */
    dialog = gtk_message_dialog_new (GTK_WINDOW (popup),
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_OTHER,
                                     GTK_BUTTONS_OK, "Error : Passport data NOT MATCHED");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
        }

    sortie4=popen("rm temp.xml", "r");
    sortie5=popen("rm temp_fac_0.jp2", "r");
	}
	//If passport not in database :
	else
	{
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

                    /* Creation of a passport add in database pop up window */
        GtkWidget *popup = NULL; //on va creer une fenetre
        GtkWidget *dialog = NULL; //et une boite de dialogue a l'intérieur de cette dernière
        popup = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée une nouvelle fenetre appelée popup
        gtk_window_set_title (GTK_WINDOW (popup), "New passport"); //titre de la fenetre
        /* Insertion de la boite de dialogue dans la fenetre popup */
        dialog = gtk_message_dialog_new (GTK_WINDOW (popup),
                                         GTK_DIALOG_MODAL,
                                         GTK_MESSAGE_OTHER,
                                         GTK_BUTTONS_OK, " -New passport-\nAdded in database");
        gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
    }

    /* Data labels update (Type, Issuer, Surname, etc...) */
    sText=(gchar*)malloc(1000*sizeof(gchar));
    pList = gtk_container_get_children (GTK_CONTAINER((GtkWidget*)data));

    tempLabel = GTK_WIDGET(pList->data);
    strcpy (sText, "Type : ");
    strcat (sText, data1[0]); // Add data to the label
    gtk_label_set_text(GTK_LABEL(tempLabel), sText); //Update label
    pList=g_list_next(pList); // Go to next label

    tempLabel = GTK_WIDGET(pList->data);
    strcpy (sText, "Issuer : ");
    strcat (sText, data1[1]); // Add data to the label
    gtk_label_set_text(GTK_LABEL(tempLabel), sText); //Update label
    pList=g_list_next(pList); // Go to next label

    tempLabel = GTK_WIDGET(pList->data);
    strcpy (sText, "Surname : ");
    strcat (sText, data1[2]); // Add data to the label
    gtk_label_set_text(GTK_LABEL(tempLabel), sText); //Update label
    pList=g_list_next(pList); // Go to next label

    tempLabel = GTK_WIDGET(pList->data);
    strcpy (sText, "Given name : ");
    strcat (sText, data1[3]); // Add data to the label
    gtk_label_set_text(GTK_LABEL(tempLabel), sText); //Update label
    pList=g_list_next(pList); // Go to next label

    tempLabel = GTK_WIDGET(pList->data);
    strcpy (sText, "Number : ");
    strcat (sText, data1[4]); // Add data to the label
    gtk_label_set_text(GTK_LABEL(tempLabel), sText); //Update label
    pList=g_list_next(pList); // Go to next label

    tempLabel = GTK_WIDGET(pList->data);
    strcpy (sText, "Nationality : ");
    strcat (sText, data1[5]); // Add data to the label
    gtk_label_set_text(GTK_LABEL(tempLabel), sText); //Update label
    pList=g_list_next(pList); // Go to next label

    tempLabel = GTK_WIDGET(pList->data);
    strcpy (sText, "Date of birth (yymmdd) : ");
    strcat (sText, data1[6]); // Add data to the label
    gtk_label_set_text(GTK_LABEL(tempLabel), sText); //Update label
    pList=g_list_next(pList); // Go to next label

    tempLabel = GTK_WIDGET(pList->data);
    strcpy (sText, "Sex : ");
    strcat (sText, data1[7]); // Add data to the label
    gtk_label_set_text(GTK_LABEL(tempLabel), sText); //Update label
    pList=g_list_next(pList); // Go to next label

    tempLabel = GTK_WIDGET(pList->data);
    strcpy (sText, "Date of expiry (yymmdd) : ");
    strcat (sText, data1[8]); // Add data to the label
    gtk_label_set_text(GTK_LABEL(tempLabel), sText); //Update label

    data1 = NULL;
    data2=NULL;

    g_free(sText);
    g_list_free(pList);

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
