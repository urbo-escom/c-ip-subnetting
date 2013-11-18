#include <gtk/gtk.h>
#include <string.h>

enum {
	COL_ID = 0,
	COL_INTERVAL_BIN_MIN,
	COL_INTERVAL_BIN_MAX,
	COL_INTERVAL_DEC_MIN,
	COL_INTERVAL_DEC_MAX,
	COL_SUBNET_ID,
	COL_SUBNET_BROAD,
	COL_HOST_MIN,
	COL_HOST_MAX,
	COL_USE,
	NUM_COLS
};

static GtkListStore* store;
static GtkTreeIter iter;

extern void Table_append(char* column) {
	char values[NUM_COLS][129];
	memset(&values, 0, sizeof(values));

	sscanf(column, "%s %s %s %s %s %s %s %s %s %s",
		values[0], values[1], values[2], values[3], values[4],
		values[5], values[6], values[7], values[8], values[9]);

	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter,
		COL_ID, values[0],
		COL_INTERVAL_BIN_MIN, values[1],
		COL_INTERVAL_BIN_MAX, values[2],
		COL_INTERVAL_DEC_MIN, values[3],
		COL_INTERVAL_DEC_MAX, values[4],
		COL_SUBNET_ID, values[5],
		COL_SUBNET_BROAD, values[6],
		COL_HOST_MIN, values[7],
		COL_HOST_MAX, values[8],
		COL_USE, values[9],
		-1);
}

extern void Table_clear() {
	gtk_list_store_clear(store);
}

static GtkWidget* create_view_and_model(void) {
	GtkCellRenderer *renderer;
	GtkWidget *view;
	GtkTreeModel *model;

	view = gtk_tree_view_new ();

	char* col_names[10] = {
		"ID net",
		"Binary interval min",
		"Binary interval max",
		"Decimal interval min",
		"Decimal interval max",
		"Subnet ID",
		"Sub broadcast",
		"Host start",
		"Host end",
		"Is Used?"};

	int i;
	for(i = 0; i < 10; i++) {
		renderer = gtk_cell_renderer_text_new ();
		g_object_set(renderer, "editable", TRUE, NULL);
		gtk_tree_view_insert_column_with_attributes(
			GTK_TREE_VIEW (view), -1, col_names[i],
		        renderer, "text", i, NULL);
	}
	store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING,
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	model = GTK_TREE_MODEL(store);
	gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

	g_object_unref (model);
	return view;
}

static GtkWidget *connection_ip, *connection_port;
static GtkWidget *connection_button;

static GtkWidget *ip_entry, *host_entry;
static GtkWidget *ip_button;

static void ip_get_table(GtkWidget* button, gpointer data);

int main(int argc, char **argv) {
	GtkWidget *window;
	GtkWidget *view;

	gtk_init (&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect (window, "delete_event",
	                  gtk_main_quit, NULL);

	view = create_view_and_model();

	GtkWidget *sw = gtk_scrolled_window_new (NULL, NULL);
	   gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),
	                                       GTK_SHADOW_ETCHED_IN);
	   gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),
	                                  GTK_POLICY_AUTOMATIC,
	                                  GTK_POLICY_AUTOMATIC);
	GtkWidget *grid = gtk_grid_new();
	   gtk_grid_set_row_spacing (GTK_GRID (grid), 6);
	   gtk_grid_set_row_homogeneous(GTK_GRID(grid), 1);
	   gtk_grid_set_column_homogeneous(GTK_GRID(grid), 1);

	connection_ip = gtk_entry_new();
	connection_port = gtk_entry_new();

	ip_entry = gtk_entry_new();
	host_entry = gtk_entry_new();

	connection_button = gtk_button_new_with_label("Connect");
	ip_button = gtk_button_new_with_label("Get table");

	g_signal_connect(G_OBJECT(ip_button),
		"clicked", G_CALLBACK(ip_get_table), NULL);

	gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 0, 0, 10, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 2, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 3, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 4, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 5, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 6, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 7, 0, 1, 10);

	gtk_grid_attach(GTK_GRID(grid), connection_button,
		1, 1, 6, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new("IP"),
		1, 2, 4, 1);
	gtk_grid_attach(GTK_GRID(grid), connection_ip,
		1, 3, 4, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Port"),
		5, 2, 4, 1);
	gtk_grid_attach(GTK_GRID(grid), connection_port,
		5, 3, 4, 1);

	gtk_container_add (GTK_CONTAINER (sw), view);

	gtk_grid_attach(GTK_GRID(grid), ip_button,
		1, 4, 8, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new("IP"),
		1, 5, 4, 1);
	gtk_grid_attach(GTK_GRID(grid), ip_entry,
		1, 6, 4, 1);
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Total hosts"),
		5, 5, 4, 1);
	gtk_grid_attach(GTK_GRID(grid), host_entry,
		5, 6, 4, 1);
	gtk_grid_attach(GTK_GRID(grid), sw,
		1, 7, 8, 3);


	gtk_container_add(GTK_CONTAINER (window), grid);
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 200);
	gtk_widget_show_all(window);

	gtk_main ();

	return 0;
}

static void ip_get_table(GtkWidget* button, gpointer data) {
	
}

