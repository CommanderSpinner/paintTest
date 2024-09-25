#include "gui.h"
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *drawing_area;

int height = 600;
int width = 800;
gboolean is_drawing = FALSE;  // Track whether the mouse button is being held down

// Store the current path the user is drawing
static GList *drawn_lines = NULL; // To store the lines as the user draws

typedef struct {
    double x, y;
} Point;

// Handle window destroy event
static void on_window_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

// Draw the lines on the drawing area
static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_rgb(cr, 0, 0, 0); // Red color

    if (drawn_lines != NULL) {
        GList *current_line = drawn_lines;
        cairo_set_line_width(cr, 2); // Set brush stroke thickness

        // Iterate over all stored points and draw them
        while (current_line != NULL) {
            Point *point = (Point *)current_line->data;

            // Draw line between successive points
            if (current_line == drawn_lines) {
                cairo_move_to(cr, point->x, point->y); // Start from the first point
            } else {
                cairo_line_to(cr, point->x, point->y); // Draw to the next point
            }

            current_line = current_line->next;
        }
        cairo_stroke(cr); // Finalize the stroke
    }

    return FALSE; // Returning FALSE lets GTK handle further drawing if needed
}

// Handle mouse button press events
static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) { // Left mouse button
        is_drawing = TRUE;  // Set drawing flag to TRUE when the button is pressed

        // Add the point to the drawing list
        Point *new_point = g_new(Point, 1);
        new_point->x = event->x;
        new_point->y = event->y;
        drawn_lines = g_list_append(drawn_lines, new_point);

        // Redraw the area
        gtk_widget_queue_draw(widget);
    }
    return TRUE;
}

// Handle mouse button release events
static gboolean on_button_release(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) { // Left mouse button
        is_drawing = FALSE;  // Stop drawing when the button is released
    }
    return TRUE;
}

// Handle mouse motion events for drawing
static gboolean on_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer data) {
    if (is_drawing) { // Only draw when the left mouse button is pressed
        // Add the point to the drawing list while dragging
        Point *new_point = g_new(Point, 1);
        new_point->x = event->x;
        new_point->y = event->y;
        drawn_lines = g_list_append(drawn_lines, new_point);

        // Redraw the area
        gtk_widget_queue_draw(widget);
    }
    return TRUE;
}

void createApp(int argc, char** argv) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Set the title of the window
    gtk_window_set_title(GTK_WINDOW(window), "Simple Paint");

    // Set the default window size
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    // Create a drawing area widget
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, width, height); // Set size of drawing area

    // Connect the draw signal of the drawing area to the callback function
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), NULL);

    // Connect mouse button press event
    g_signal_connect(G_OBJECT(drawing_area), "button-press-event", G_CALLBACK(on_button_press), NULL);

    // Connect mouse button release event
    g_signal_connect(G_OBJECT(drawing_area), "button-release-event", G_CALLBACK(on_button_release), NULL);

    // Connect mouse motion event to handle drawing
    g_signal_connect(G_OBJECT(drawing_area), "motion-notify-event", G_CALLBACK(on_motion_notify), NULL);

    // Enable event mask for mouse events (press + release + motion)
    gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK);

    // Add the drawing area to the window
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Connect the signal to handle window closing
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    // Show all widgets inside the window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();
}

void cleanUp() {
    // Free all the points stored in drawn_lines
    g_list_free_full(drawn_lines, g_free);
}



/*
GtkWidget *window;
GtkWidget *drawing_area;

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

    // -------------------- looki looki
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

}*/
