/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "userUtils.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

extern user* user_list_head;
extern user* user_list_tail;

GtkWidget *window1;
GdkPixbuf *window1_icon_pixbuf;
GtkWidget *vbox1;
GtkWidget *vpaned1;
GtkWidget *hbox4;
GtkWidget *scrolledwindow1;
GtkWidget *treeview;
GtkWidget *vbox3;
GtkWidget *frame1;
GtkWidget *alignment1;
GtkWidget *entry1;
GtkWidget *label2;
GtkWidget *hbox5;
GtkWidget *bt_refrush;
GtkWidget *scrolledwindow2;
GtkWidget *textview;
GtkWidget *hbox7;
GtkWidget *bt_send;
GtkWidget *alignment4;
GtkWidget *hbox8;
GtkWidget *image2;
GtkWidget *label4;
GtkWidget *bt_close;
GtkWidget *cb_packet;
GtkTreeStore *store;
GtkTreeIter iter;
GtkCellRenderer *renderer;
GtkTreeSelection *selection;

GtkWidget*
create_window1 (void)
{
  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window1, 350, 430);
  gtk_window_set_title (GTK_WINDOW (window1), _("\351\243\236\351\270\275\344\274\240\344\271\246(Linux\347\211\210)"));
  gtk_window_set_position (GTK_WINDOW (window1), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable (GTK_WINDOW (window1), FALSE);
  window1_icon_pixbuf = create_pixbuf ("ipmsg.xpm");
  if (window1_icon_pixbuf)
    {
      gtk_window_set_icon (GTK_WINDOW (window1), window1_icon_pixbuf);
      gdk_pixbuf_unref (window1_icon_pixbuf);
    }

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (window1), vbox1);

  vpaned1 = gtk_vpaned_new ();
  gtk_widget_show (vpaned1);
  gtk_box_pack_start (GTK_BOX (vbox1), vpaned1, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vpaned1), 4);
  gtk_paned_set_position (GTK_PANED (vpaned1), 130);

  hbox4 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox4);
  gtk_paned_pack1 (GTK_PANED (vpaned1), hbox4, FALSE, TRUE);
  gtk_widget_set_size_request (hbox4, -1, 120);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (hbox4), scrolledwindow1, TRUE, TRUE, 0);
  gtk_widget_set_size_request (scrolledwindow1, 250, 55);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_SHADOW_IN);

  treeview = gtk_tree_view_new ();

    store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    user* p;
	for(p = user_list_head; p != NULL; p = p->next){
        gtk_tree_store_append(store, &iter, NULL);

        gtk_tree_store_set(store, &iter, COLUMN_USER, p->user_name,
                                            COLUMN_HOST, p->host_name,
                                            COLUMN_IP, inet_ntoa((p->address).sin_addr),
                                            COLUMN_LOGIN, p->load_name,
                                            -1);
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                COLUMN_USER,
                                                "User Name", renderer,
                                                "text", COLUMN_USER,
                                                NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                COLUMN_GROUP,
                                                "Group", renderer,
                                                "text", COLUMN_GROUP,
                                                NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                COLUMN_HOST,
                                                "Host Name", renderer,
                                                "text", COLUMN_HOST,
                                                NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                COLUMN_IP,
                                                "IP", renderer,
                                                "text", COLUMN_IP,
                                                NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                COLUMN_LOGIN,
                                                "Login Name", renderer,
                                                "text", COLUMN_LOGIN,
                                                NULL);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    g_signal_connect(selection, "changed",
                G_CALLBACK(on_changed), NULL);

  gtk_widget_show (treeview);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), treeview);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox3);
  gtk_box_pack_start (GTK_BOX (hbox4), vbox3, TRUE, TRUE, 5);
  gtk_widget_set_size_request (vbox3, 100, -1);

  frame1 = gtk_frame_new (NULL);
  gtk_widget_show (frame1);
  gtk_box_pack_start (GTK_BOX (vbox3), frame1, TRUE, TRUE, 5);

  alignment1 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment1);
  gtk_container_add (GTK_CONTAINER (frame1), alignment1);
  gtk_widget_set_size_request (alignment1, 0, 0);
  gtk_container_set_border_width (GTK_CONTAINER (alignment1), 6);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment1), 2, 2, 10, 10);

  entry1 = gtk_entry_new ();
  gtk_widget_show (entry1);
  gtk_container_add (GTK_CONTAINER (alignment1), entry1);
  gtk_editable_set_editable (GTK_EDITABLE (entry1), FALSE);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry1), 9679);

  label2 = gtk_label_new (_("<b>\347\224\250\346\210\267</b>"));
  gtk_widget_show (label2);
  gtk_frame_set_label_widget (GTK_FRAME (frame1), label2);
  gtk_label_set_use_markup (GTK_LABEL (label2), TRUE);
  gtk_label_set_line_wrap (GTK_LABEL (label2), TRUE);

  hbox5 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox5);
  gtk_box_pack_start (GTK_BOX (vbox3), hbox5, FALSE, TRUE, 10);

  bt_refrush = gtk_button_new_from_stock ("gtk-refresh");
  gtk_widget_show (bt_refrush);
  gtk_box_pack_start (GTK_BOX (hbox5), bt_refrush, FALSE, TRUE, 6);
  g_signal_connect ((gpointer) bt_refrush, "clicked",
                    G_CALLBACK (refrush),
                    NULL);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow2);
  gtk_paned_pack2 (GTK_PANED (vpaned1), scrolledwindow2, TRUE, TRUE);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_SHADOW_IN);

  textview = gtk_text_view_new ();
  gtk_widget_show (textview);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), textview);
  gtk_widget_set_size_request (textview, -1, 200);
  gtk_text_view_set_accepts_tab (GTK_TEXT_VIEW (textview), FALSE);
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW (textview), GTK_WRAP_CHAR);

  hbox7 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox7);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox7, TRUE, TRUE, 0);
  gtk_widget_set_size_request (hbox7, -1, 1);

  bt_send = gtk_button_new ();
  gtk_widget_show (bt_send);
  gtk_box_pack_start (GTK_BOX (hbox7), bt_send, FALSE, TRUE, 8);
  gtk_widget_set_size_request (bt_send, -1, 30);
  gtk_container_set_border_width (GTK_CONTAINER (bt_send), 2);
  g_signal_connect ((gpointer) bt_send, "clicked",
                    G_CALLBACK (bt_send_clicked),
                    textview);

  alignment4 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment4);
  gtk_container_add (GTK_CONTAINER (bt_send), alignment4);

  hbox8 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox8);
  gtk_container_add (GTK_CONTAINER (alignment4), hbox8);

  image2 = gtk_image_new_from_stock ("gtk-redo", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image2);
  gtk_box_pack_start (GTK_BOX (hbox8), image2, FALSE, FALSE, 0);

  label4 = gtk_label_new_with_mnemonic (_("\345\217\221\351\200\201  "));
  gtk_widget_show (label4);
  gtk_box_pack_start (GTK_BOX (hbox8), label4, FALSE, FALSE, 0);

  bt_close = gtk_button_new_from_stock ("gtk-close");
  gtk_widget_show (bt_close);
  gtk_box_pack_start (GTK_BOX (hbox7), bt_close, FALSE, TRUE, 8);
  gtk_widget_set_size_request (bt_close, -1, 30);
  gtk_container_set_border_width (GTK_CONTAINER (bt_close), 2);

  cb_packet = gtk_check_button_new_with_mnemonic (_("\345\260\201\350\243\205"));
  gtk_widget_show (cb_packet);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_packet), TRUE);
  gtk_box_pack_start (GTK_BOX (hbox7), cb_packet, FALSE, FALSE, 33);
  g_signal_connect ((gpointer) cb_packet, "toggled",
    G_CALLBACK ( packet_send ), NULL );

  g_signal_connect ((gpointer) window1, "destroy",
                    G_CALLBACK (closeApp),
                    NULL);
  g_signal_connect_swapped ((gpointer) bt_close, "clicked",
                            G_CALLBACK (gtk_widget_hide),
                            GTK_OBJECT (window1));

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (window1, window1, "window1");
  GLADE_HOOKUP_OBJECT (window1, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT (window1, vpaned1, "vpaned1");
  GLADE_HOOKUP_OBJECT (window1, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow1, "scrolledwindow1");
  GLADE_HOOKUP_OBJECT (window1, treeview, "treeview");
  GLADE_HOOKUP_OBJECT (window1, vbox3, "vbox3");
  GLADE_HOOKUP_OBJECT (window1, frame1, "frame1");
  GLADE_HOOKUP_OBJECT (window1, alignment1, "alignment1");
  GLADE_HOOKUP_OBJECT (window1, entry1, "entry1");
  GLADE_HOOKUP_OBJECT (window1, label2, "label2");
  GLADE_HOOKUP_OBJECT (window1, hbox5, "hbox5");
  GLADE_HOOKUP_OBJECT (window1, bt_refrush, "bt_refrush");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow2, "scrolledwindow2");
  GLADE_HOOKUP_OBJECT (window1, textview, "textview");
  GLADE_HOOKUP_OBJECT (window1, hbox7, "hbox7");
  GLADE_HOOKUP_OBJECT (window1, bt_send, "bt_send");
  GLADE_HOOKUP_OBJECT (window1, alignment4, "alignment4");
  GLADE_HOOKUP_OBJECT (window1, hbox8, "hbox8");
  GLADE_HOOKUP_OBJECT (window1, image2, "image2");
  GLADE_HOOKUP_OBJECT (window1, label4, "label4");
  GLADE_HOOKUP_OBJECT (window1, bt_close, "bt_close");
  GLADE_HOOKUP_OBJECT (window1, cb_packet, "cb_packet");

  return window1;
}

