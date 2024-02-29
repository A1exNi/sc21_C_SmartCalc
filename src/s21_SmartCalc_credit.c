#include "s21_SmartCalc.h"

void credit_calc(gpointer window) {
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  gtk_window_set_child(window, vbox);
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  gtk_box_append(GTK_BOX(vbox), hbox);
  GtkWidget *menu = set_menu(1);
  gtk_box_append(GTK_BOX(hbox), menu);
  GtkWidget *name_menu = gtk_label_new_with_mnemonic("Credit Calcuator");
  gtk_box_append(GTK_BOX(hbox), name_menu);
  GtkWidget *grid = gtk_grid_new();
  grid_setings(grid, 10, -1, 10, -1, 10, 10);
  gtk_box_append(GTK_BOX(vbox), grid);
  grid_credit_fill(grid);
  GtkWidget *label_3 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_3),
                       "<span size=\"120%\">Interest rate</span>");
  gtk_widget_set_halign(label_3, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_3, 0, 2, 1, 1);
  GtkWidget *entry_3 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), entry_3, 1, 2, 1, 1);
  label_3 = gtk_label_new_with_mnemonic("%");
  gtk_grid_attach(GTK_GRID(grid), label_3, 2, 2, 1, 1);
  GtkWidget *label_4 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_4),
                       "<span size=\"120%\">Type of monthly pay</span>");
  gtk_widget_set_halign(label_4, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_4, 0, 3, 1, 1);
  GtkWidget *button_1 = gtk_check_button_new_with_label("Annuity");
  gtk_check_button_set_active(GTK_CHECK_BUTTON(button_1), TRUE);
  gtk_grid_attach(GTK_GRID(grid), button_1, 1, 3, 1, 1);
  GtkWidget *button_2 = gtk_check_button_new_with_label("Differentiated");
  gtk_check_button_set_group(GTK_CHECK_BUTTON(button_2),
                             GTK_CHECK_BUTTON(button_1));
  gtk_grid_attach(GTK_GRID(grid), button_2, 1, 4, 1, 1);
  GtkWidget *button_calc = gtk_button_new_with_label("CALCULATE");
  gtk_widget_set_margin_start(button_calc, 10);
  gtk_widget_set_margin_end(button_calc, 10);
  gtk_widget_set_margin_top(button_calc, 10);
  gtk_box_append(GTK_BOX(vbox), button_calc);
  g_signal_connect(button_calc, "clicked", G_CALLBACK(proc_credit), vbox);
  gtk_window_present(GTK_WINDOW(window));
}

void grid_credit_fill(GtkWidget *grid) {
  GtkWidget *label_1 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_1),
                       "<span size=\"120%\">Amount of credit</span>");
  gtk_grid_attach(GTK_GRID(grid), label_1, 0, 0, 1, 1);
  gtk_widget_set_halign(label_1, GTK_ALIGN_START);
  GtkWidget *entry_1 = gtk_entry_new();
  gtk_entry_set_input_purpose(GTK_ENTRY(entry_1), GTK_INPUT_PURPOSE_DIGITS);
  gtk_grid_attach(GTK_GRID(grid), entry_1, 1, 0, 1, 1);
  char char_rub[4] = {-30, -126, -67, 0};
  label_1 = gtk_label_new_with_mnemonic(char_rub);
  gtk_grid_attach(GTK_GRID(grid), label_1, 2, 0, 1, 1);
  GtkWidget *label_2 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_2),
                       "<span size=\"120%\">Credit time</span>");
  gtk_widget_set_halign(label_2, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_2, 0, 1, 1, 1);
  GtkWidget *hbox_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  gtk_grid_attach(GTK_GRID(grid), hbox_2, 1, 1, 1, 1);
  GtkWidget *entry_2 = gtk_entry_new();
  gtk_box_append(GTK_BOX(hbox_2), entry_2);
  char **name_drop_down = g_strsplit("years months", " ", -1);
  GtkWidget *drop_down =
      gtk_drop_down_new_from_strings((const char **)name_drop_down);
  gtk_box_append(GTK_BOX(hbox_2), drop_down);
  g_strfreev(name_drop_down);
}

void proc_credit(GtkWidget *button, gpointer vbox) {
  GtkWidget *grid_data = gtk_widget_get_prev_sibling(button);
  GtkWidget *amount_entry = gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 0);
  GtkEntryBuffer *buffer_amount = gtk_entry_get_buffer(GTK_ENTRY(amount_entry));
  const char *str_amount = gtk_entry_buffer_get_text(buffer_amount);
  GtkWidget *time_hbox = gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 1);
  GtkWidget *time_entry = gtk_widget_get_first_child(time_hbox);
  GtkEntryBuffer *buffer_time = gtk_entry_get_buffer(GTK_ENTRY(time_entry));
  const char *str_time = gtk_entry_buffer_get_text(buffer_time);
  GtkWidget *drop_down = gtk_widget_get_next_sibling(time_entry);
  guint id_drop_down = gtk_drop_down_get_selected(GTK_DROP_DOWN(drop_down));
  GtkWidget *rate_entry = gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 2);
  GtkEntryBuffer *buffer_rate = gtk_entry_get_buffer(GTK_ENTRY(rate_entry));
  const char *str_rate = gtk_entry_buffer_get_text(buffer_rate);
  GtkWidget *rad_button = gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 3);
  gboolean is_annuity =
      gtk_check_button_get_active(GTK_CHECK_BUTTON(rad_button));
  if (str_amount[0] && str_time[0] && str_rate[0]) {
    guint error = 0;
    error = check_str_amount_for_error(str_amount, error);
    error = check_str_time_for_error(str_time, error, id_drop_down);
    error = check_str_rate_for_error(str_rate, error);
    GtkWidget *grid = gtk_widget_get_next_sibling(button);
    if (grid) {
      for (int i = 0; i < 3; i++) gtk_grid_remove_row(GTK_GRID(grid), 0);
    } else {
      grid = gtk_grid_new();
      grid_setings(grid, 10, 20, 10, -1, 50, 20);
      gtk_box_append(GTK_BOX(vbox), grid);
    }
    if (!error) {
      double mon_pay, total_pay, over_pay;
      char *str_list_mon_pay = calloc(1, sizeof(char));
      calculate_credit(str_amount, str_time, str_rate, id_drop_down, is_annuity,
                       &str_list_mon_pay, &mon_pay, &total_pay, &over_pay);
      print_answer(grid, mon_pay, total_pay, over_pay, str_list_mon_pay,
                   is_annuity);
      free(str_list_mon_pay);
    } else {
      print_error(grid, error);
    }
  }
}

void calculate_credit(const char *str_amount, const char *str_time,
                      const char *str_rate, guint id_drop_down,
                      gboolean is_annuity, char **str_list_mon_pay,
                      double *mon_pay, double *total_pay, double *over_pay) {
  *total_pay = 0;
  double amount = 0;
  sscanf(str_amount, "%lf", &amount);
  double time = 0;
  sscanf(str_time, "%lf", &time);
  double rate = 0;
  sscanf(str_rate, "%lf", &rate);
  if (id_drop_down == 0) time *= 12.0;
  double p = rate / 12.0 / 100.0;
  if (is_annuity) {
    *mon_pay = amount * (p + p / (pow((1.0 + p), time) - 1.0));
    *mon_pay = round(*mon_pay * 100.0) / 100.0;
    *total_pay = *mon_pay * time;
    *over_pay = *total_pay - amount;
  } else {
    double b = amount / time;
    for (int j = 0; j < time; j++) {
      double i = (amount - j * b) * p;
      *mon_pay = b + i;
      *mon_pay = round(*mon_pay * 100.0) / 100.0;
      char str_mon_pay[1024] = {0};
      sprintf(str_mon_pay, "%.2f", *mon_pay);
      char *buf = g_strconcat(*str_list_mon_pay, str_mon_pay, NULL);
      free(*str_list_mon_pay);
      *str_list_mon_pay = buf;
      if (j < time - 1) {
        buf = g_strconcat(*str_list_mon_pay, " ", NULL);
        free(*str_list_mon_pay);
        *str_list_mon_pay = buf;
      }
      *total_pay += *mon_pay;
    }
    *over_pay = *total_pay - amount;
  }
}

void print_answer(GtkWidget *grid, double mon_pay, double total_pay,
                  double over_pay, char *str_list_mon_pay,
                  gboolean is_annuity) {
  char str_mon_pay[1024] = {0};
  sprintf(str_mon_pay, "%s%.2f%s", "<span size=\"120%\">", mon_pay, "</span>");
  char str_total_pay[1024] = {0};
  sprintf(str_total_pay, "%s%.2f%s", "<span size=\"120%\">", total_pay,
          "</span>");
  char str_over_pay[1024] = {0};
  sprintf(str_over_pay, "%s%.2f%s", "<span size=\"120%\">", over_pay,
          "</span>");
  GtkWidget *label_1 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_1),
                       "<span size=\"120%\">Monthly payment</span>");
  gtk_widget_set_halign(label_1, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_1, 0, 0, 1, 1);
  if (is_annuity) {
    GtkWidget *label_12 = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_12), str_mon_pay);
    gtk_widget_set_halign(label_12, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_12, 1, 0, 1, 1);
  } else {
    char **name_drop_down;
    name_drop_down = g_strsplit(str_list_mon_pay, " ", -1);
    GtkWidget *drop_down =
        gtk_drop_down_new_from_strings((const char **)name_drop_down);
    gtk_grid_attach(GTK_GRID(grid), drop_down, 1, 0, 1, 1);
    g_strfreev(name_drop_down);
  }
  GtkWidget *label_2 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_2),
                       "<span size=\"120%\">Overpayment</span>");
  gtk_widget_set_halign(label_2, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_2, 0, 1, 1, 1);
  GtkWidget *label_22 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_22), str_over_pay);
  gtk_widget_set_halign(label_22, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), label_22, 1, 1, 1, 1);
  GtkWidget *label_3 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_3),
                       "<span size=\"120%\">Total payment</span>");
  gtk_widget_set_halign(label_3, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_3, 0, 2, 1, 1);
  GtkWidget *label_32 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_32), str_total_pay);
  gtk_widget_set_halign(label_32, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), label_32, 1, 2, 1, 1);
}

void print_error(GtkWidget *grid, guint error) {
  GtkWidget *label_1 = gtk_label_new(NULL);
  if (error == 1)
    gtk_label_set_markup(
        GTK_LABEL(label_1),
        "<span color=\"red\">*AMOUNT OF CREDIT can be in the "
        "format\n\"999.99\". The minimum allowed value is 1.</span>");
  else if (error == 2)
    gtk_label_set_markup(GTK_LABEL(label_1),
                         "<span color=\"red\">*CREDIT TIME must be an integer "
                         "in the range\nfrom 1 to 50 for \"yeara\" and from 1 "
                         "to 600\nfor \"month\".</span>");
  else if (error == 3)
    gtk_label_set_markup(GTK_LABEL(label_1),
                         "<span color=\"red\">*INTEREST RATE must be between "
                         "0.01 and 999.</span>");
  gtk_widget_set_halign(label_1, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_1, 0, 0, 1, 1);
}