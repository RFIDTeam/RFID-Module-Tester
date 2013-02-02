#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "xmlReader.h"

int main (int argc, char *argv[])
{

    GtkWidget *win = NULL; // fenetre
    GtkWidget *hbox = NULL; // large Hbox contenant vboxG et vboxD
    GtkWidget *vbox = NULL;
    GtkWidget *vboxG = NULL; // Vbox de gauche
    GtkWidget *vboxC = NULL; // vboxCenter
    GtkWidget *vboxD = NULL; // Vbox de droite
    GtkWidget *champMRZ = NULL; // champ dans lequel nous allons écrire la MRZ
    GtkWidget *bouton = NULL; // va créer chaque bouton
    GtkWidget *label = NULL;
    GtkWidget *labelSurName = NULL;
    GtkWidget *labelNationality = NULL;
    GtkWidget *labelDateOfBirth = NULL;
    GtkWidget *labelType = NULL;
    GtkWidget *labelIssuer = NULL;
    GtkWidget *labelGivenName = NULL;
    GtkWidget *labelNumber = NULL;
    GtkWidget *labelSex = NULL;
    GtkWidget *labelDateOfExpiry = NULL;
    GtkWidget *zone_texte = NULL;
    GtkWidget *scrolled_win = NULL;
    GtkWidget *image = NULL;
    GtkWidget *logo = NULL;
    GtkWidget *frame = NULL;
    GtkWidget *hboxbuttons =NULL;

    /* Initialize GTK+ */

    gtk_init (&argc, &argv);

    /* Creation of the main window */
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée la fenetre
    gtk_container_set_border_width (GTK_CONTAINER (win), 5); //définit la taille de la bordure de la fenetre
    gtk_window_set_default_size(GTK_WINDOW(win),500,440); // dimensionne la fenetre
    gtk_window_set_title (GTK_WINDOW (win), "CheckMyPassport"); //donne un titre à la fenetre
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER); //centre la fenetre à son ouverture
    g_signal_connect (win, "destroy", gtk_main_quit, NULL); // Connecte le bouton de fermeture de la fenetre à la fermeture de la fenetre


    /*---------------------Creation of the main element : THE vbox ---------------*/

    vbox = gtk_vbox_new(FALSE,0);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    /* Insertion of the logo */
    logo = gtk_image_new_from_file("checkmypassport.png");
    gtk_box_pack_start (GTK_BOX (vbox), logo, FALSE, FALSE, 1);

    /* Under the logo : Creation of a large Hbox */
    hbox = gtk_hbox_new (TRUE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);


    /* -----------In the large Hbox : Creation of a frame for PASSPORT INFORMATIONS----------------- */

    frame = gtk_frame_new ("Passport Informations");
    gtk_box_pack_start (GTK_BOX (hbox), frame, TRUE, TRUE, 1);

    /* Creation of the Left vbox */
    vboxG = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (frame), vboxG);

    gchar* sUtf8;

    /* Label Type */
    sUtf8 = (gchar*)malloc(15*sizeof(gchar));
    sUtf8 = g_locale_to_utf8("Type : ", -1, NULL, NULL, NULL); //Converting to UTF8
    labelType = gtk_label_new(sUtf8);
    gtk_label_set_justify(GTK_LABEL(labelType), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vboxG), labelType, FALSE, FALSE, 3);  //Inserting label into vboxG
    g_free(sUtf8);
    /* Label Issuer */
    sUtf8 = (gchar*)malloc(150*sizeof(gchar));
    sUtf8 = g_locale_to_utf8("Issuer : ", -1, NULL, NULL, NULL); //Converting to UTF8
    labelIssuer = gtk_label_new(sUtf8);
    gtk_label_set_justify(GTK_LABEL(labelIssuer), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vboxG), labelIssuer, FALSE, FALSE, 3);  //Inserting label into vboxG

    /* Label Surname */
    sUtf8 = g_locale_to_utf8("Surname : ", -1, NULL, NULL, NULL); //Converting to UTF8
    label = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vboxG), label, FALSE, FALSE, 3);  //Inserting label into vboxG

        /* Label Given Name */
    sUtf8 = g_locale_to_utf8("Given name : ", -1, NULL, NULL, NULL); //Converting to UTF8
    label = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vboxG), label, FALSE, FALSE, 3);  //Inserting label into vboxG

        /* Label Number */
    sUtf8 = g_locale_to_utf8("Number : ", -1, NULL, NULL, NULL); //Converting to UTF8
    label = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vboxG), label, FALSE, FALSE, 3);  //Inserting label into vboxG

        /* Label Nationality */
    sUtf8 = g_locale_to_utf8("Nationality : ", -1, NULL, NULL, NULL); //Converting to UTF8
    label = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vboxG), label, FALSE, FALSE, 3);  //Inserting label into vboxG

        /* Label Date of birth */
    sUtf8 = g_locale_to_utf8("Date of birth (yymmdd) : ", -1, NULL, NULL, NULL); //Converting to UTF8
    label = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vboxG), label, FALSE, FALSE, 3);  //Inserting label into vboxG

    /* Label Sex */
    sUtf8 = g_locale_to_utf8("Sex : ", -1, NULL, NULL, NULL); //Converting to UTF8
    label = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vboxG), label, FALSE, FALSE, 3);  //Inserting label into vboxG

    /* Label Date of Expiry */
    sUtf8 = g_locale_to_utf8("Date of expiry (yymmdd) : ", -1, NULL, NULL, NULL); //Converting to UTF8
    label = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vboxG), label, FALSE, FALSE, 3);  //Inserting label into vboxG

    /* --------------- Creation de la Vbox Center------------------- */
    vboxC = gtk_vbox_new (TRUE, 0);
    gtk_container_add (GTK_CONTAINER (hbox), vboxC);
    /* Putting image in VboxCenter */
    image = gtk_image_new();
    gtk_box_pack_start (GTK_BOX (vboxC), image, TRUE, TRUE, 0);


    /* Creation of the text zone */
    zone_texte = gtk_text_view_new();
    scrolled_win = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start (GTK_BOX(vboxG), scrolled_win, TRUE, TRUE,0);
    gtk_container_add (GTK_CONTAINER(scrolled_win), zone_texte);

    /* Creation of the MRZ Entry */
    champMRZ = gtk_entry_new();
    gtk_entry_set_text(champMRZ, "Write here the 2nd MRZ line");
    gtk_entry_set_max_length(champMRZ, 44);
    //Insertion du champ dans la vboxD
    gtk_box_pack_start(GTK_BOX(vboxG), champMRZ, FALSE, FALSE, 0);

    /* Creation of the buttons hbox */
    hboxbuttons = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vboxG), hboxbuttons);

    /* -----------------Creation des boutons----------------------------- */

    //Bouton GOOOOOOOOO//
    bouton = gtk_button_new_from_stock ("Check!");
    g_signal_connect (G_OBJECT (bouton), "clicked", G_CALLBACK (copierMRZ), (GtkWidget*) champMRZ);
    g_signal_connect (G_OBJECT (bouton), "clicked", G_CALLBACK (lancer), (GtkWidget*) vboxG);
    g_signal_connect (G_OBJECT (bouton), "clicked", G_CALLBACK (showPhoto), (GtkWidget*) vboxC);
    gtk_box_pack_start (GTK_BOX (hboxbuttons), bouton, TRUE, TRUE, 1); // également faisable avec  gtk_container_add (GTK_CONTAINER (vbox), button2);

    //Bouton Help //
    bouton = gtk_button_new_from_stock ("Help");
    g_signal_connect (G_OBJECT (bouton), "clicked", G_CALLBACK (Readme), (gpointer) hbox);
    gtk_box_pack_start (GTK_BOX (hboxbuttons), bouton, FALSE, FALSE, 2); // également faisable avec  gtk_container_add (GTK_CONTAINER (vbox), button2);

    //Bouton Quitter//
    bouton = gtk_button_new_from_stock (GTK_STOCK_QUIT);
    g_signal_connect (bouton, "clicked", gtk_main_quit, NULL);
    gtk_box_pack_start (GTK_BOX (hboxbuttons), bouton, FALSE, FALSE, 1);

    fct_ouvrir (win, zone_texte);
//    open_file (file_name, GTK_TEXT_VIEW (user_data));
//    showPhoto(win, vboxC);

    /* Enter the main loop */

    gtk_widget_show_all (win);
    gtk_main ();

    return EXIT_SUCCESS;
}
