#include <gtk/gtk.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
 
#define MAXRCVLEN 500
#define PORTNUM 2343
 
static const char* Client_get_message() {
   static char buffer[MAXRCVLEN + 1];
   int len, mysocket;
   struct sockaddr_in dest; 
 
   mysocket = socket(AF_INET, SOCK_STREAM, 0);
 
   memset(&dest, 0, sizeof(dest));
   dest.sin_family = AF_INET;
   dest.sin_addr.s_addr = inet_addr("127.0.0.1");
   dest.sin_port = htons(PORTNUM);
 
   connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
 
   len = recv(mysocket, buffer, MAXRCVLEN, 0);


   buffer[len] = '\0';
   printf("Response: %s\n", buffer);
 
   close(mysocket);
   return buffer;
}

static void on_button_click(GtkButton *button, gpointer user_data) {
  GtkEntry *entry = GTK_ENTRY(user_data);

  const char *name = Client_get_message();

  gtk_entry_set_text(entry, name);
}



static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *grid;
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *entry;

  window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "To the server and beyond");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  button = gtk_button_new_with_label("What does the server says?");
  entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), "click on the button");

  grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 10, 1);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 8, 1);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

  g_signal_connect(GTK_BUTTON(button),
                   "clicked", 
                    G_CALLBACK(on_button_click),
                    entry);

  gtk_container_add(GTK_CONTAINER(window),
                    GTK_WIDGET(grid));

  gtk_widget_show_all(window);
}



int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example",
                            G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app,
                      "activate",
                      G_CALLBACK(activate),
                      NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

