#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "userUtils.h"
#include "main.h"

extern GtkWidget * treeview;
extern GtkCellRenderer *renderer;
extern GtkTreeStore *store;
extern user* user_list_head;
extern user* user_list_tail;

gchar *send_ip;
gboolean is_packet = TRUE;

void closeApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}

void refrush(GtkWidget *window, gpointer data)
{

    GtkTreeIter iter;
    GtkWidget *entry;
    gchar str_num[32];
    int user_count = 0;
    user* p;


    gtk_tree_store_clear(store);

	for(p = user_list_head; p != NULL; p = p->next){
        gtk_tree_store_append(store, &iter, NULL);

        gtk_tree_store_set(store, &iter, COLUMN_USER, p->user_name,
                                            COLUMN_HOST, p->host_name,
                                            COLUMN_IP, inet_ntoa((p->address).sin_addr),
                                            COLUMN_LOGIN, p->load_name,
                                            -1);
        user_count ++;
	}

	entry = lookup_widget(GTK_WIDGET(window), "entry1");
    g_assert(entry);
    snprintf(str_num, 31, "%d", user_count);
    gtk_entry_set_text(GTK_ENTRY(entry), str_num);

}

void bt_send_clicked(GtkWidget *window, gpointer data)
{
    GtkTextBuffer *buffer;
    GtkTextIter start,end;
    char *msg_text;
    struct sockaddr_in client_address;

    if (send_ip == NULL)
        return;
    client_address.sin_family = AF_INET;
	client_address.sin_port = htons(2425);
	client_address.sin_addr.s_addr = inet_addr(send_ip);
    printf("%s\n",send_ip);
    buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW((GtkWidget *) data));
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    const GtkTextIter s=start,e=end;
    msg_text=gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),&s,&e,FALSE);

    if (is_packet == TRUE)
        send_msg_packet(msg_text, 0, 2, client_address);
    else
        send_msg_packet(msg_text, 0, 1, client_address);

    printf("%s\n",msg_text);
}

void packet_send(GtkCheckButton *button, gpointer data)
{
    if ( gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( button ) ) ) {
        is_packet = TRUE;
    } else {
        is_packet = FALSE;
    }
}

gboolean on_changed(GtkTreeSelection *selection, gpointer label)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    //printf("onchange\n");
    if (gtk_tree_selection_get_selected(
        selection, &model, &iter)) {

        gtk_tree_model_get(model, &iter, COLUMN_IP, &send_ip,  -1);

        //g_free(send_ip);
    }

    return TRUE;
}
