#include "./../include/callback.h"
//#define _POSIX_C_SOURCE  2

#define DEFAULT_FILE "main.c"

static void open_file (const gchar *, GtkTextView *);



void fct_ouvrir(GtkWidget *wid, gpointer user_data)
{
    GtkWidget *selectionneur = NULL;

    selectionneur = gtk_file_chooser_dialog_new ("Quel fichier souhaitez vous afficher?", NULL,
                                                 GTK_FILE_CHOOSER_ACTION_OPEN,
                                                 GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);

    if (gtk_dialog_run (GTK_DIALOG (selectionneur)) == GTK_RESPONSE_ACCEPT)
    {
        gchar *file_name = NULL;

        file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (selectionneur));
        open_file (file_name, GTK_TEXT_VIEW (user_data));
        g_free (file_name), file_name = NULL;
    }
    gtk_widget_destroy (selectionneur);

//  (void) *wid;
}

void salutMonde (GtkWidget *wid, gpointer win)
{

    char tampon[UCHAR_MAX];
    FILE *sortie;

    sortie=popen("cd /home/sarah/wzmrtd \n ./wzmrtd-tool -r '#1' -f -pfx test -xsi", "r");
    //sortie=popen("cd /home/sarah/wzmrtd \n ./wzmrtd-tool -r '#1' -z ""$(echo -e 'P<MARSALLOUH<<SABRINA<<<<<<<<<<<<<<<<<<<<<<<\r\nEV02120860MAR8807113F1511114BE812755<<<<<<78')"" -f -pfx SABRINA", "r")

    while (fgets (tampon, sizeof tampon, sortie) != NULL)
    {
        fputs (tampon, stdout);
    }

    fclose (sortie);

    GtkWidget *dialog = NULL;
    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "AAAAaaaaaaaaaaaaaah!");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

static void open_file (const gchar *file_name, GtkTextView *zone_texte)
{
    g_return_if_fail (file_name && zone_texte);
    {
        gchar *contents = NULL;

        if (g_file_get_contents (file_name, &contents, NULL, NULL))
        {
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
        else
        {
            printf ("Impossible d'ouvrir le fichier %s\n", file_name);
        }
    }
}