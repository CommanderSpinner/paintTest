#include <gtk/gtk.h>
static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data);
extern GtkWidget *window;
extern GtkWidget *drawing_area;

extern int height;
extern int width;

static void on_window_destroy(GtkWidget *widget, gpointer data);

void createApp(int argc, char** argv);

void cleanUp();