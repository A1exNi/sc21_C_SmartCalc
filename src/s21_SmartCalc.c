#include "s21_SmartCalc.h"

int main(int argc, char **argv) {
  GtkApplication *app =
      gtk_application_new("smart.calc.ilanadah", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}

void activate(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "SmartCalc_v1.0");
  gtk_window_set_default_size(GTK_WINDOW(window), 325, 550);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  main_calc(window);
}

GtkWidget *set_menu(int row) {
  char name[4] = {-30, -119, -95, 0};
  char s[1024] = {0};
  sprintf(s, "%s%s%s", SET_SIZE_BEGIN_170, name, SET_SIZE_END);
  GtkWidget *menu_button = gtk_menu_button_new();
  GtkWidget *label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), s);
  gtk_menu_button_set_child(GTK_MENU_BUTTON(menu_button), label);
  gtk_menu_button_set_has_frame(GTK_MENU_BUTTON(menu_button), FALSE);
  GtkWidget *box = gtk_list_box_new();
  char names_box[5][20] = {"Main Calculator", "Credit Calculator",
                           "Deposit Calculator", "Plotting a Function", "Quit"};
  for (int i = 0; i < 5; i++) {
    label = gtk_label_new(names_box[i]);
    gtk_widget_set_size_request(label, 50, 50);
    if (i == 4)
      gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    else
      gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_box_append(GTK_LIST_BOX(box), label);
  }
  GtkListBoxRow *box_row =
      gtk_list_box_get_row_at_index(GTK_LIST_BOX(box), row);
  gtk_list_box_select_row(GTK_LIST_BOX(box), box_row);
  GtkWidget *popover = gtk_popover_new();
  gtk_popover_set_has_arrow(GTK_POPOVER(popover), FALSE);
  g_signal_connect(box, "row_activated", G_CALLBACK(window_select), NULL);
  gtk_widget_set_halign(popover, GTK_ALIGN_START);
  gtk_popover_set_child(GTK_POPOVER(popover), box);
  gtk_menu_button_set_popover(GTK_MENU_BUTTON(menu_button), popover);
  return menu_button;
}

void window_select(GtkWidget *list_box) {
  GtkWidget *window = gtk_widget_get_ancestor(list_box, GTK_TYPE_WINDOW);
  GtkWidget *popover = gtk_widget_get_ancestor(list_box, GTK_TYPE_POPOVER);
  gtk_widget_set_visible(popover, FALSE);
  GtkListBoxRow *row = gtk_list_box_get_selected_row(GTK_LIST_BOX(list_box));
  GtkWidget *label = gtk_list_box_row_get_child(row);
  const char *s = gtk_label_get_label(GTK_LABEL(label));
  if (s[0] == 'Q') {
    gtk_window_close(GTK_WINDOW(window));
  } else {
    if (s[0] == 'M') {
      main_calc(window);
    }
    if (s[0] == 'C') {
      credit_calc(window);
    }
    if (s[0] == 'D') {
      depos_calc(window);
    }
    if (s[0] == 'P') {
      int minmax[4] = {5, -5, 5, -5};
      plot_calc(window, TRUE, NULL, minmax, FALSE);
    }
  }
}

guint check_str_amount_for_error(const char *str_amount, guint answer) {
  guint count = 0;
  for (char *ptr = (char *)str_amount; *ptr && !answer; ptr++) {
    if (*ptr == '.' || *ptr == ',') {
      ptr++;
      while (*ptr && !answer) {
        if (*ptr >= '0' && *ptr <= '9') {
          count++;
          if (count > 2) answer = 1;
        } else {
          answer = 1;
        }
        ptr++;
      }
      ptr--;
    } else if (*ptr < '0' || *ptr > '9')
      answer = 1;
  }
  return answer;
}

guint check_str_time_for_error(const char *str_time, guint answer,
                               guint id_drop_down) {
  guint count = 0;
  for (char *ptr = (char *)str_time; *ptr && !answer; ptr++) {
    if (*ptr < '0' || *ptr > '9')
      answer = 2;
    else
      count++;
    if (id_drop_down == 0 && count > 2)
      answer = 2;
    else if (id_drop_down == 1 && count > 3)
      answer = 2;
  }
  if (answer == 0) {
    guint number = 0;
    sscanf(str_time, "%u", &number);
    if (id_drop_down == 0 && (number == 0 || number > 50)) answer = 2;
    if (id_drop_down == 1 && (number == 0 || number > 600)) answer = 2;
    if (id_drop_down == 2 && (number == 0 || number > 18250)) answer = 2;
  }
  return answer;
}

guint check_str_rate_for_error(const char *str_rate, guint answer) {
  guint count = 0;
  for (char *ptr = (char *)str_rate; *ptr && !answer; ptr++) {
    if (*ptr == '.') *ptr = ',';
    if (*ptr == ',') {
      ptr++;
      while (*ptr && !answer) {
        if (*ptr >= '0' && *ptr <= '9') {
          count++;
          if (count > 2) answer = 3;
        } else {
          answer = 3;
        }
        ptr++;
      }
      ptr--;
    } else if (*ptr < '0' || *ptr > '9')
      answer = 3;
  }
  if (answer == 0) {
    double number = 0;
    sscanf(str_rate, "%lf", &number);
    if (number == 0 || number > 999.0) answer = 3;
  }
  return answer;
}

guint check_str_date_for_error(const char *date_str, guint error) {
  char *ptr = (char *)date_str;
  int count_day = 0;
  int count_month = 0;
  int count_year = 0;
  count_day = count_number_from_str(ptr, &error);
  if (count_day != 2) {
    error = 4;
  } else {
    count_month = count_number_from_str(ptr + count_day + 1, &error);
    if (count_month != 2) {
      error = 4;
    } else {
      count_year =
          count_number_from_str(ptr + count_day + count_month + 2, &error);
      if (count_year != 4) error = 4;
    }
  }
  if (!error) {
    int day;
    int month;
    int year;
    int scan_number = sscanf(date_str, "%d.%d.%d", &day, &month, &year);
    if (scan_number != 3) error = 4;
    if (!g_date_valid_dmy(day, month, year)) error = 4;
  }
  return error;
}

guint count_number_from_str(char *ptr, guint *error) {
  int count = 0;
  while (*ptr && *ptr != '.' && !(*error)) {
    if (*ptr >= '0' && *ptr <= '9')
      count++;
    else
      *error = 4;
    ptr++;
  }
  return count;
}

void grid_setings(GtkWidget *grid, int margin_start, int margin_top,
                  int margin_end, int margin_bottom, int column_spacing,
                  int row_spacing) {
  if (margin_start > 0) gtk_widget_set_margin_start(grid, margin_start);
  if (margin_top > 0) gtk_widget_set_margin_top(grid, margin_top);
  if (margin_end > 0) gtk_widget_set_margin_end(grid, margin_end);
  if (margin_bottom > 0) gtk_widget_set_margin_bottom(grid, margin_bottom);
  if (column_spacing > 0)
    gtk_grid_set_column_spacing(GTK_GRID(grid), column_spacing);
  if (row_spacing > 0) gtk_grid_set_row_spacing(GTK_GRID(grid), row_spacing);
}