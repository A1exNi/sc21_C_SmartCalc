#include "s21_SmartCalc.h"

void plot_calc(gpointer window, gboolean activ, char *expression,
               int minmax_buf[4], gboolean print_e) {
  int len = 10000;
  static int minmax[4] = {5, -5, 5, -5};
  for (int i = 0; i < 4; i++) minmax[i] = minmax_buf[i];
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  gtk_window_set_child(window, vbox);
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  gtk_box_append(GTK_BOX(vbox), hbox);
  GtkWidget *menu = set_menu(3);
  gtk_box_append(GTK_BOX(hbox), menu);
  GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 90);
  gtk_box_append(GTK_BOX(hbox), hbox2);
  GtkWidget *name_menu = gtk_label_new_with_mnemonic("Plotting a Function");
  gtk_box_append(GTK_BOX(hbox2), name_menu);
  GtkWidget *hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_append(GTK_BOX(hbox2), hbox3);
  GtkWidget *button_switch = gtk_toggle_button_new();
  GtkWidget *label_name_sw;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_switch), activ);
  gtk_widget_set_size_request(button_switch, 80, 1);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_switch)))
    label_name_sw = gtk_label_new_with_mnemonic("Function");
  else
    label_name_sw = gtk_label_new_with_mnemonic("Graph");
  gtk_button_set_child(GTK_BUTTON(button_switch), label_name_sw);
  g_signal_connect(button_switch, "toggled", G_CALLBACK(set_plot_window),
                   minmax);
  gtk_box_append(GTK_BOX(hbox3), button_switch);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_switch))) {
    int len_data = 1 + 4 + len;
    static double data[1 + 4 + 2000001] = {0};
    data[0] = len_data;
    for (int i = 0; i < 4; i++) data[i + 1] = minmax[i];
    guint error = 0;
    calc_y(data, expression, &error);
    if (!error) {
      gtk_box_set_spacing(GTK_BOX(vbox), 1);
      GtkWidget *area = gtk_drawing_area_new();
      gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(area), 325);
      gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(area), 500);
      gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), draw_area, data,
                                     NULL);
      gtk_box_append(GTK_BOX(vbox), area);
    } else {
      plot_calc(window, FALSE, NULL, minmax, TRUE);
    }
  } else {
    draw_calc(vbox, minmax, print_e);
  }
  gtk_window_present(GTK_WINDOW(window));
}

void set_plot_window(GtkWidget *button, gpointer minmax) {
  GtkWidget *window = gtk_widget_get_ancestor(button, GTK_TYPE_WINDOW);
  if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) {
    plot_calc(window, FALSE, NULL, minmax, FALSE);
  } else {
    GtkWidget *vbox = gtk_window_get_child(GTK_WINDOW(window));
    GtkWidget *hbox = gtk_widget_get_first_child(vbox);
    hbox = gtk_widget_get_next_sibling(hbox);
    hbox = gtk_widget_get_next_sibling(hbox);
    hbox = gtk_widget_get_next_sibling(hbox);
    hbox = gtk_widget_get_next_sibling(hbox);
    GtkWidget *child = gtk_widget_get_first_child(hbox);
    child = gtk_widget_get_next_sibling(child);
    ((int *)minmax)[0] =
        gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(child));
    child = gtk_widget_get_next_sibling(child);
    ((int *)minmax)[1] =
        gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(child));
    hbox = gtk_widget_get_next_sibling(hbox);
    child = gtk_widget_get_first_child(hbox);
    child = gtk_widget_get_next_sibling(child);
    ((int *)minmax)[2] =
        gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(child));
    child = gtk_widget_get_next_sibling(child);
    ((int *)minmax)[3] =
        gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(child));
    plot_calc(window, TRUE, NULL, minmax, FALSE);
  }
}

void calc_y(double *data, char *expression, guint *error) {
  int len = 10000;
  if (expression) {
    guint j = 0;
    for (double i = data[2]; i <= data[1]; i += (data[1] - data[2]) / len) {
      char str_i[1024] = {0};
      sprintf(str_i, "%f", i);
      data[5 + j] = result_calculation(str_i, expression, error);
      j++;
    }
  } else {
    data[0] = 0;
  }
}

void draw_calc(GtkWidget *vbox, int minmax[4], gboolean print_e) {
  gtk_box_set_spacing(GTK_BOX(vbox), 3);
  GtkWidget *label_entry = gtk_label_new(NULL);
  gtk_label_set_ellipsize(GTK_LABEL(label_entry), PANGO_ELLIPSIZE_START);
  gtk_label_set_xalign(GTK_LABEL(label_entry), 1);
  gtk_widget_set_margin_end(label_entry, 10);
  if (print_e) gtk_label_set_label(GTK_LABEL(label_entry), "=");
  gtk_box_append(GTK_BOX(vbox), label_entry);
  label_entry = gtk_label_new(NULL);
  gtk_widget_set_margin_end(label_entry, 10);
  gtk_label_set_xalign(GTK_LABEL(label_entry), 1);
  gtk_label_set_ellipsize(GTK_LABEL(label_entry), PANGO_ELLIPSIZE_START);
  char label_string[1024] = {0};
  if (print_e)
    sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300, "ERROR", SET_SIZE_END);
  else
    sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300, "0", SET_SIZE_END);
  gtk_label_set_markup(GTK_LABEL(label_entry), label_string);
  gtk_box_append(GTK_BOX(vbox), label_entry);
  GtkWidget *hbox6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 120);
  gtk_widget_set_margin_start(hbox6, 30);
  gtk_box_append(GTK_BOX(vbox), hbox6);
  GtkWidget *label_max = gtk_label_new_with_mnemonic("max:");
  gtk_box_append(GTK_BOX(hbox6), label_max);
  GtkWidget *label_min = gtk_label_new_with_mnemonic("min:");
  gtk_box_append(GTK_BOX(hbox6), label_min);
  GtkWidget *hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_widget_set_halign(hbox4, GTK_ALIGN_END);
  gtk_box_append(GTK_BOX(vbox), hbox4);
  GtkWidget *label_x = gtk_label_new_with_mnemonic("x:");
  gtk_box_append(GTK_BOX(hbox4), label_x);
  GtkAdjustment *adjustment =
      gtk_adjustment_new(minmax[0], 5, 1000000, 1, 5, 0);
  GtkWidget *spin_button = gtk_spin_button_new(adjustment, 10, 0);
  gtk_box_append(GTK_BOX(hbox4), spin_button);
  GtkAdjustment *adjustment2 =
      gtk_adjustment_new(minmax[1], -1000000, -5, 1, 5, 0);
  GtkWidget *spin_button2 = gtk_spin_button_new(adjustment2, 10, 0);
  gtk_box_append(GTK_BOX(hbox4), spin_button2);
  GtkWidget *hbox5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_widget_set_halign(hbox5, GTK_ALIGN_END);
  gtk_box_append(GTK_BOX(vbox), hbox5);
  GtkWidget *label_y = gtk_label_new_with_mnemonic("y:");
  gtk_box_append(GTK_BOX(hbox5), label_y);
  GtkAdjustment *adjustment3 =
      gtk_adjustment_new(minmax[2], 5, 1000000, 1, 5, 0);
  GtkWidget *spin_button3 = gtk_spin_button_new(adjustment3, 10, 0);
  gtk_box_append(GTK_BOX(hbox5), spin_button3);
  GtkAdjustment *adjustment4 =
      gtk_adjustment_new(minmax[3], -1000000, -5, 1, 5, 0);
  GtkWidget *spin_button4 = gtk_spin_button_new(adjustment4, 10, 0);
  gtk_box_append(GTK_BOX(hbox5), spin_button4);
  GtkEventController *control_key = gtk_event_controller_key_new();
  g_signal_connect_swapped(control_key, "key-pressed", G_CALLBACK(key_pressed),
                           label_entry);
  gtk_widget_add_controller(vbox, control_key);
  set_button_for_calc(vbox, hbox6, 'p');
}

void draw_area(GtkDrawingArea *area, cairo_t *cr, int width, int height,
               gpointer data) {
  int len = 10000;
  double max_x = ((double *)data)[1];
  double min_x = ((double *)data)[2];
  double max_y = ((double *)data)[3];
  double min_y = ((double *)data)[4];
  double len_x = max_x - min_x;
  double len_y = max_y - min_y;
  double indent_x = 15, indent_y = 10;
  double cx = width / (len_x / fabs(min_x));
  double cy = height / (len_y / fabs(max_y));
  draw_arrow(cr, cx, cy, width, height);
  draw_grid_x(cr, cx, cy, max_x, min_x, width, height, indent_x);
  draw_grid_y(cr, cx, cy, max_y, min_y, width, height, indent_y);
  if (((double *)data)[0] > 0 && area) {
    cairo_set_source_rgba(cr, 255, 0, 0, 1);
    cairo_set_line_width(cr, 3);
    double step_x = (width - indent_x * 2) / len_x;
    double step_y = (height - indent_y * 2) / len_y;
    int j = 5;
    cairo_move_to(cr, cx + ((double *)data)[2] * step_x,
                  cy - ((double *)data)[j] * step_y);
    for (double i = ((double *)data)[2]; i <= ((double *)data)[1];
         i += len_x / len) {
      cairo_line_to(cr, cx + i * step_x, cy - ((double *)data)[j] * step_y);
      cairo_move_to(cr, cx + i * step_x, cy - ((double *)data)[j + 1] * step_y);
      j++;
    }
    cairo_stroke(cr);
  }
}

void draw_arrow(cairo_t *cr, double cx, double cy, int width, int height) {
  cairo_set_source_rgba(cr, 0, 0, 0, 1);
  cairo_set_line_width(cr, 1);
  cairo_move_to(cr, cx, 0);
  cairo_line_to(cr, cx + 7, 7);
  cairo_move_to(cr, cx, 0);
  cairo_line_to(cr, cx - 7, 7);
  cairo_move_to(cr, cx - 15, 7);
  cairo_show_text(cr, "y");
  cairo_move_to(cr, cx, 0);
  cairo_line_to(cr, cx, height);
  cairo_move_to(cr, 0, cy);
  cairo_line_to(cr, width, cy);
  cairo_line_to(cr, width - 7, cy + 7);
  cairo_move_to(cr, width, cy);
  cairo_line_to(cr, width - 7, cy - 7);
  cairo_show_text(cr, "x");
  cairo_move_to(cr, cx - 10, cy + 15);
  cairo_show_text(cr, "0");
  cairo_stroke(cr);
}

void draw_grid_x(cairo_t *cr, double cx, double cy, double max_x, double min_x,
                 int width, int height, double indent_x) {
  double x_grid_frequency = 10;
  double len_x = max_x - min_x;
  char str[1024] = {0};
  cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
  cairo_move_to(cr, cx, 0);
  double x = 0;
  double b_width = cx;
  while (x < max_x) {
    x += len_x / x_grid_frequency;
    b_width += (width - indent_x * 2) / x_grid_frequency;
    cairo_move_to(cr, b_width, 0);
    cairo_line_to(cr, b_width, height);
  }
  cairo_stroke(cr);
  cairo_set_source_rgba(cr, 0, 0, 0, 1);
  if (b_width > width) {
    cairo_move_to(cr, b_width - 10 - (width - indent_x * 2) / x_grid_frequency,
                  cy + 15);
    sprintf(str, "%.1f", x + len_x / x_grid_frequency);
  } else {
    cairo_move_to(cr, b_width - 10, cy + 15);
    sprintf(str, "%.1f", x);
  }
  cairo_show_text(cr, str);
  cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
  cairo_move_to(cr, cx, 0);
  x = 0;
  b_width = cx;
  while (x > min_x) {
    x -= len_x / x_grid_frequency;
    b_width -= (width - indent_x * 2) / x_grid_frequency;
    cairo_move_to(cr, b_width, 0);
    cairo_line_to(cr, b_width, height);
  }
  cairo_stroke(cr);
  cairo_set_source_rgba(cr, 0, 0, 0, 1);
  if (b_width < 0) {
    cairo_move_to(cr, b_width - 10 + (width - indent_x * 2) / x_grid_frequency,
                  cy + 15);
    sprintf(str, "%.1f", x + len_x / x_grid_frequency);
  } else {
    cairo_move_to(cr, b_width - 10, cy + 15);
    sprintf(str, "%.1f", x);
  }
  cairo_show_text(cr, str);
}

void draw_grid_y(cairo_t *cr, double cx, double cy, double max_y, double min_y,
                 int width, int height, double indent_y) {
  double y_grid_frequency = 15;
  double len_y = max_y - min_y;
  char str[1024] = {0};
  cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
  cairo_move_to(cr, 0, cy);
  double y = 0;
  double b_height = cy;
  while (y < max_y) {
    y += len_y / y_grid_frequency;
    b_height -= (height - indent_y * 2) / y_grid_frequency;
    cairo_move_to(cr, 0, b_height);
    cairo_line_to(cr, width, b_height);
  }
  cairo_stroke(cr);
  cairo_set_source_rgba(cr, 0, 0, 0, 1);
  if (b_height < 0) {
    cairo_move_to(cr, cx + 10,
                  b_height + 5 + (height - indent_y * 2) / y_grid_frequency);
    sprintf(str, "%.1f", y - len_y / y_grid_frequency);
  } else {
    cairo_move_to(cr, cx + 10, b_height + 5);
    sprintf(str, "%.1f", y);
  }
  cairo_show_text(cr, str);
  cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
  cairo_move_to(cr, 0, cy);
  y = 0;
  b_height = cy;
  while (y > min_y) {
    y -= len_y / y_grid_frequency;
    b_height += (height - indent_y * 2) / y_grid_frequency;
    cairo_move_to(cr, 0, b_height);
    cairo_line_to(cr, width, b_height);
  }
  cairo_stroke(cr);
  cairo_set_source_rgba(cr, 0, 0, 0, 1);
  if (b_height > height) {
    cairo_move_to(cr, cx + 10,
                  b_height + 5 - (height - indent_y * 2) / y_grid_frequency);
    sprintf(str, "%.1f", y + len_y / y_grid_frequency);
  } else {
    cairo_move_to(cr, cx + 10, b_height + 5);
    sprintf(str, "%.1f", y);
  }
  cairo_show_text(cr, str);
}

void proc_for_ploting_calc(GtkWidget *prev_label_entry,
                           GtkWidget *label_entry) {
  const char *buf = gtk_label_get_label(GTK_LABEL(prev_label_entry));
  char expression[520] = {0};
  int len = cut_label(buf, expression);
  expression[len - 2] = '\0';
  int minmax[4] = {0};
  GtkWidget *window = gtk_widget_get_ancestor(label_entry, GTK_TYPE_WINDOW);
  GtkWidget *hbox_min_max = gtk_widget_get_next_sibling(label_entry);
  GtkWidget *hbox_x = gtk_widget_get_next_sibling(hbox_min_max);
  GtkWidget *label_x = gtk_widget_get_first_child(hbox_x);
  GtkWidget *spin_x_max = gtk_widget_get_next_sibling(label_x);
  minmax[0] = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_x_max));
  GtkWidget *spin_x_min = gtk_widget_get_next_sibling(spin_x_max);
  minmax[1] = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_x_min));
  GtkWidget *hbox_y = gtk_widget_get_next_sibling(hbox_x);
  GtkWidget *label_y = gtk_widget_get_first_child(hbox_y);
  GtkWidget *spin_y_max = gtk_widget_get_next_sibling(label_y);
  minmax[2] = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_y_max));
  GtkWidget *spin_y_min = gtk_widget_get_next_sibling(spin_y_max);
  minmax[3] = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_y_min));
  plot_calc(window, TRUE, expression, minmax, FALSE);
}