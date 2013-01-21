 #include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"


int main (int argc, char *argv[])
{

  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;

  /* Initialize GTK+ */

  gtk_init (&argc, &argv);

  /* Creation de la fenetre principale */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL); // Crée la fenetre

  gtk_container_set_border_width (GTK_CONTAINER (win), 20); //définit la taille de la bordure de la fenetre
  gtk_window_set_default_size(GTK_WINDOW(win),300,200); // dimensionne la fenetre
  gtk_window_set_title (GTK_WINDOW (win), "Fenetre principale"); //donne un titre à la fenetre
  gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER); //centre la fenetre à son ouverture
//  gtk_widget_realize (win); // Facultatif??
  g_signal_connect (win, "destroy", gtk_main_quit, NULL); // Connecte le bouton de fermeture de la fenetre à la fermeture de la fenetre

  /* Creation de la vertical box */
  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  /* Creation de la zone de texte */

  GtkWidget *zone_texte = NULL;
  GtkWidget *scrolled_win = NULL;

  zone_texte = gtk_text_view_new();
  scrolled_win = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start (GTK_BOX(vbox), scrolled_win, TRUE, TRUE,0);
  gtk_container_add (GTK_CONTAINER(scrolled_win), zone_texte);


  /* Creation des boutons */
  GtkWidget *bouton = NULL;

  //Bouton OUVRIR//
  bouton = gtk_button_new_from_stock ("Afficher fichier...");
  g_signal_connect (G_OBJECT (bouton), "clicked", G_CALLBACK (fct_ouvrir), zone_texte);
  gtk_box_pack_start (GTK_BOX (vbox), bouton, FALSE, FALSE, 2);

  //Bouton 2 //
  bouton = gtk_button_new_from_stock ("Changer dir");
  g_signal_connect (G_OBJECT (bouton), "clicked", G_CALLBACK (fct_ouvrir2), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), bouton, FALSE, FALSE, 2); // également faisable avec  gtk_container_add (GTK_CONTAINER (vbox), button2);

  //Bouton 3//
  bouton = gtk_button_new_from_stock ("Lancer!");
  g_signal_connect (G_OBJECT (bouton), "clicked", G_CALLBACK (lancer), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), bouton, FALSE, FALSE, 2); // également faisable avec  gtk_container_add (GTK_CONTAINER (vbox), button2);


  //Bouton Quitter//
  bouton = gtk_button_new_from_stock (GTK_STOCK_QUIT);
  g_signal_connect (bouton, "clicked", gtk_main_quit, NULL);
  gtk_box_pack_start (GTK_BOX (vbox), bouton, FALSE, FALSE, 2);


  /* Enter the main loop */

  gtk_widget_show_all (win);
  gtk_main ();

  return EXIT_SUCCESS;
}
