#include "gui.h"
GtkWidget *window;
static void on_window_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // Set the drawing color to red
    cairo_set_source_rgb(cr, 1, 0, 0); // Red color

    // Draw a rectangle
    cairo_rectangle(cr, 10, 10, 100, 100);
    cairo_fill(cr); // Fill the rectangle

    return FALSE; // Returning FALSE means GTK will handle the default drawing
}

void createApp(int argc, char** argv){
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Set the title of the window
    gtk_window_set_title(GTK_WINDOW(window), "Paint Test");

    // Set the default window size
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Connect the draw signal of the drawing area to the callback function
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), NULL);

    // Add the drawing area to the window
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Connect the signal to handle window closing
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    // Show the window
    gtk_widget_show(window);

    // Start the GTK main loop
    gtk_main();
}

void cleanUp(){

}