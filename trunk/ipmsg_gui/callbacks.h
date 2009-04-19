#include <gtk/gtk.h>


void closeApp(GtkWidget *window, gpointer data);

void refrush(GtkWidget *window, gpointer data);

void bt_send_clicked(GtkWidget *window, gpointer data);

void packet_send(GtkCheckButton *button, gpointer data);

gboolean on_changed(GtkTreeSelection *selection, gpointer label);
