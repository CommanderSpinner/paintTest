#include <gtk/gtk.h>
static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data);
extern GtkWidget *window;

static void on_window_destroy(GtkWidget *widget, gpointer data);

void createApp(int argc, char** argv);

void cleanUp();