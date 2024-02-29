#include "s21_SmartCalc.h"

void depos_calc(gpointer window) {
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  gtk_window_set_child(window, vbox);
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  gtk_box_append(GTK_BOX(vbox), hbox);
  GtkWidget *menu = set_menu(2);
  gtk_box_append(GTK_BOX(hbox), menu);
  GtkWidget *name_menu = gtk_label_new_with_mnemonic("Deposit Calcuator");
  gtk_box_append(GTK_BOX(hbox), name_menu);
  GtkWidget *grid = gtk_grid_new();
  grid_setings(grid, 10, -1, 10, -1, 10, 10);
  gtk_box_append(GTK_BOX(vbox), grid);
  grid_depos_fill(grid);
  GtkWidget *label_4 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_4),
                       "<span size=\"120%\">Tax rate</span>");
  gtk_widget_set_halign(label_4, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_4, 0, 3, 1, 1);
  GtkWidget *entry_4 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), entry_4, 1, 3, 1, 1);
  label_4 = gtk_label_new_with_mnemonic("%");
  gtk_grid_attach(GTK_GRID(grid), label_4, 2, 3, 1, 1);
  GtkWidget *label_5 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_5),
                       "<span size=\"120%\">Frequency of pay</span>");
  gtk_widget_set_halign(label_5, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_5, 0, 4, 1, 1);
  char **name_drop_down = g_strsplit(
      "every day|every week|once a month|once a quarter|once in half-year|once "
      "a year|at the end",
      "|", -1);
  GtkWidget *drop_down_2 =
      gtk_drop_down_new_from_strings((const char **)name_drop_down);
  gtk_grid_attach(GTK_GRID(grid), drop_down_2, 1, 4, 1, 1);
  g_strfreev(name_drop_down);
  GtkWidget *button_1 = gtk_check_button_new_with_label("Capitalization");
  gtk_grid_attach(GTK_GRID(grid), button_1, 1, 5, 1, 1);
  add_list(vbox, "Replenishment");
  add_list(vbox, "Part withdrawal");
  GtkWidget *button_calc = gtk_button_new_with_label("CALCULATE");
  gtk_widget_set_margin_start(button_calc, 10);
  gtk_widget_set_margin_end(button_calc, 10);
  gtk_widget_set_margin_top(button_calc, 10);
  gtk_box_append(GTK_BOX(vbox), button_calc);
  g_signal_connect(button_calc, "clicked", G_CALLBACK(proc_depos), vbox);
  gtk_window_present(GTK_WINDOW(window));
}

void grid_depos_fill(GtkWidget *grid) {
  GtkWidget *label_1 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_1),
                       "<span size=\"120%\">Amount of deposit</span>");
  gtk_grid_attach(GTK_GRID(grid), label_1, 0, 0, 1, 1);
  gtk_widget_set_halign(label_1, GTK_ALIGN_START);
  GtkWidget *entry_1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), entry_1, 1, 0, 1, 1);
  char char_rub[4] = {-30, -126, -67, 0};
  label_1 = gtk_label_new_with_mnemonic(char_rub);
  gtk_grid_attach(GTK_GRID(grid), label_1, 2, 0, 1, 1);
  GtkWidget *label_2 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_2),
                       "<span size=\"120%\">Deposit time</span>");
  gtk_widget_set_halign(label_2, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_2, 0, 1, 1, 1);
  GtkWidget *hbox_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  gtk_grid_attach(GTK_GRID(grid), hbox_2, 1, 1, 1, 1);
  GtkWidget *entry_2 = gtk_entry_new();
  gtk_box_append(GTK_BOX(hbox_2), entry_2);
  char **name_drop_down = g_strsplit("years months days", " ", -1);
  GtkWidget *drop_down =
      gtk_drop_down_new_from_strings((const char **)name_drop_down);
  gtk_box_append(GTK_BOX(hbox_2), drop_down);
  g_strfreev(name_drop_down);
  GtkWidget *label_3 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_3),
                       "<span size=\"120%\">Interest rate</span>");
  gtk_widget_set_halign(label_3, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_3, 0, 2, 1, 1);
  GtkWidget *entry_3 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), entry_3, 1, 2, 1, 1);
  label_3 = gtk_label_new_with_mnemonic("%");
  gtk_grid_attach(GTK_GRID(grid), label_3, 2, 2, 1, 1);
}

void add_list(GtkWidget *vbox, char *name_label) {
  GtkWidget *grid = gtk_grid_new();
  grid_setings(grid, 10, 10, 10, -1, 10, 10);
  gtk_box_append(GTK_BOX(vbox), grid);
  GtkWidget *label_7 = gtk_label_new(NULL);
  char label_string[1024] = {0};
  sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_120, name_label, SET_SIZE_END);
  gtk_label_set_markup(GTK_LABEL(label_7), label_string);
  gtk_widget_set_halign(label_7, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_7, 0, 0, 1, 1);
  GtkWidget *vbox_popover_for_list = my_drop_down_button(vbox, name_label);
  GtkWidget *button2 = gtk_menu_button_new();
  GtkWidget *label = gtk_label_new("+");
  gtk_menu_button_set_child(GTK_MENU_BUTTON(button2), label);
  GtkWidget *popover = gtk_popover_new();
  gtk_popover_set_has_arrow(GTK_POPOVER(popover), FALSE);
  gtk_menu_button_set_popover(GTK_MENU_BUTTON(button2), popover);
  GtkWidget *vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_popover_set_child(GTK_POPOVER(popover), vbox2);
  char **name_drop_down =
      g_strsplit("one-time|once a month|once a year", "|", -1);
  GtkWidget *drop_down =
      gtk_drop_down_new_from_strings((const char **)name_drop_down);
  gtk_box_append(GTK_BOX(vbox2), drop_down);
  g_strfreev(name_drop_down);
  GtkWidget *entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "dd.mm.yyyy");
  gtk_box_append(GTK_BOX(vbox2), entry);
  GtkWidget *entry2 = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Amount");
  gtk_box_append(GTK_BOX(vbox2), entry2);
  char name[4] = {-30, -100, -109, 0};
  GtkWidget *button_3 = gtk_button_new_with_label(name);
  gtk_box_append(GTK_BOX(vbox2), button_3);
  if (name_label[0] == 'R')
    g_signal_connect(button_3, "clicked", G_CALLBACK(add_list_button),
                     vbox_popover_for_list);
  else
    g_signal_connect(button_3, "clicked", G_CALLBACK(add_list_button),
                     vbox_popover_for_list);
  gtk_grid_attach(GTK_GRID(grid), button2, 2, 0, 1, 1);
}

GtkWidget *my_drop_down_button(GtkWidget *vbox, char *name_label) {
  GtkWidget *button_list = gtk_menu_button_new();
  gtk_widget_set_margin_start(button_list, 10);
  gtk_widget_set_margin_top(button_list, 10);
  gtk_widget_set_margin_end(button_list, 10);
  char label_name_for_button[100] = {0};
  char name[4] = {-30, -106, -68, 0};
  if (name_label[0] == 'R')
    sprintf(label_name_for_button, "%s\t%s", "Replenishment list", name);
  else
    sprintf(label_name_for_button, "%s\t%s", "Partial withdrawal list", name);
  GtkWidget *label = gtk_label_new(label_name_for_button);
  gtk_widget_set_halign(label, GTK_ALIGN_START);
  gtk_menu_button_set_child(GTK_MENU_BUTTON(button_list), label);
  GtkWidget *popover = gtk_popover_new();
  gtk_widget_set_size_request(popover, 305, 90);
  gtk_popover_set_has_arrow(GTK_POPOVER(popover), FALSE);
  GtkWidget *scrolled_win = gtk_scrolled_window_new();
  GtkWidget *vbox_popover = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
  gtk_popover_set_child(GTK_POPOVER(popover), scrolled_win);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_win),
                                vbox_popover);
  gtk_menu_button_set_popover(GTK_MENU_BUTTON(button_list), popover);
  gtk_box_append(GTK_BOX(vbox), button_list);
  return vbox_popover;
}

void add_list_button(GtkWidget *button, gpointer vbox_popover_for_list) {
  GtkWidget *popover = gtk_widget_get_ancestor(button, GTK_TYPE_POPOVER);
  GtkWidget *entry_amount = gtk_widget_get_prev_sibling(button);
  GtkEntryBuffer *entry_buffer_amount =
      gtk_entry_get_buffer(GTK_ENTRY(entry_amount));
  const char *amount_str =
      gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(entry_buffer_amount));
  GtkWidget *entry_date = gtk_widget_get_prev_sibling(entry_amount);
  GtkEntryBuffer *entry_buffer_date =
      gtk_entry_get_buffer(GTK_ENTRY(entry_date));
  const char *date_str =
      gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(entry_buffer_date));
  guint len_date_str = gtk_entry_buffer_get_length(entry_buffer_date);
  GtkWidget *drop_down = gtk_widget_get_prev_sibling(entry_date);
  guint id_drop_down = gtk_drop_down_get_selected(GTK_DROP_DOWN(drop_down));
  char drop_str[13] = {0};
  if (id_drop_down == 0)
    sprintf(drop_str, "%s", "one-time");
  else if (id_drop_down == 1)
    sprintf(drop_str, "%s", "once a month");
  else if (id_drop_down == 2)
    sprintf(drop_str, "%s", "once a year");
  if (date_str[0] && amount_str[0]) {
    guint error = 0;
    if (len_date_str != 10)
      error = 4;
    else
      error = check_str_date_for_error(date_str, error);
    error = check_str_amount_for_error(amount_str, error);
    GtkWidget *window = gtk_widget_get_ancestor(button, GTK_TYPE_WINDOW);
    GtkWidget *vbox = gtk_window_get_child(GTK_WINDOW(window));
    GtkWidget *button_c = get_button_in_depos(vbox);
    GtkWidget *grid = gtk_widget_get_next_sibling(button_c);
    if (grid) {
      for (int i = 0; i < 3; i++) gtk_grid_remove_row(GTK_GRID(grid), 0);
    } else {
      grid = gtk_grid_new();
      grid_setings(grid, 10, 10, 10, -1, -1, -1);
      gtk_box_append(GTK_BOX(vbox), grid);
    }
    func_error(error, grid);
    if (error == 1 || error == 4)
      gtk_widget_set_visible(popover, FALSE);
    else
      add_data_to_drop_depos(drop_str, date_str, amount_str,
                             vbox_popover_for_list);
  }
}

void func_error(guint error, GtkWidget *grid) {
  if (error == 1) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(
        GTK_LABEL(label),
        "<span color=\"red\">*AMOUNT can be in the format\n\"999.99\". The "
        "minimum allowed value is 1.</span>");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
  } else if (error == 4) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label),
                         "<span color=\"red\">*INVALID date format</span>");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
  }
}

GtkWidget *get_button_in_depos(GtkWidget *vbox) {
  GtkWidget *child = gtk_widget_get_first_child(vbox);
  child = gtk_widget_get_next_sibling(child);
  child = gtk_widget_get_next_sibling(child);
  child = gtk_widget_get_next_sibling(child);
  child = gtk_widget_get_next_sibling(child);
  child = gtk_widget_get_next_sibling(child);
  child = gtk_widget_get_next_sibling(child);
  return child;
}

void add_data_to_drop_depos(char *drop_str, const char *date_str,
                            const char *amount_str,
                            gpointer vbox_popover_for_list) {
  char *list = calloc(1, sizeof(char));
  char *buf =
      g_strconcat(list, drop_str, "\t", date_str, "\t", amount_str, NULL);
  GtkWidget *label_for_list = gtk_label_new_with_mnemonic(buf);
  free(list);
  free(buf);
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_box_append(GTK_BOX(vbox_popover_for_list), hbox);
  gtk_box_append(GTK_BOX(hbox), label_for_list);
  char name[4] = {-30, -99, -116, 0};
  GtkWidget *button_del = gtk_button_new_with_label(name);
  gtk_button_set_has_frame(GTK_BUTTON(button_del), FALSE);
  gtk_box_append(GTK_BOX(hbox), button_del);
  g_signal_connect(button_del, "clicked", G_CALLBACK(del_row_from_list),
                   vbox_popover_for_list);
}

void del_row_from_list(GtkWidget *button_del, gpointer vbox) {
  GtkWidget *hbox = gtk_widget_get_ancestor(button_del, GTK_TYPE_BOX);
  gtk_box_remove(GTK_BOX(vbox), hbox);
}

void proc_depos(GtkWidget *button, gpointer vbox) {
  GtkWidget *hbox = gtk_widget_get_first_child(vbox);
  GtkWidget *grid_data = gtk_widget_get_next_sibling(hbox);
  GtkWidget *amount_entry = gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 0);
  GtkEntryBuffer *buffer_amount = gtk_entry_get_buffer(GTK_ENTRY(amount_entry));
  const char *str_amount = gtk_entry_buffer_get_text(buffer_amount);
  GtkWidget *time_hbox = gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 1);
  GtkWidget *time_entry = gtk_widget_get_first_child(time_hbox);
  GtkEntryBuffer *buffer_time = gtk_entry_get_buffer(GTK_ENTRY(time_entry));
  const char *str_time = gtk_entry_buffer_get_text(buffer_time);
  GtkWidget *drop_down = gtk_widget_get_next_sibling(time_entry);
  guint id_depos_time = gtk_drop_down_get_selected(GTK_DROP_DOWN(drop_down));
  GtkWidget *rate_iterest_entry =
      gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 2);
  GtkEntryBuffer *buffer_iterest_rate =
      gtk_entry_get_buffer(GTK_ENTRY(rate_iterest_entry));
  const char *str_iterest_rate = gtk_entry_buffer_get_text(buffer_iterest_rate);
  GtkWidget *rate_tax_entry = gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 3);
  GtkEntryBuffer *buffer_tax_rate =
      gtk_entry_get_buffer(GTK_ENTRY(rate_tax_entry));
  const char *str_tax_rate = gtk_entry_buffer_get_text(buffer_tax_rate);
  GtkWidget *drop_down_freq = gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 4);
  guint id_freq_pay = gtk_drop_down_get_selected(GTK_DROP_DOWN(drop_down_freq));
  GtkWidget *check_button = gtk_grid_get_child_at(GTK_GRID(grid_data), 1, 5);
  gboolean is_capitalization =
      gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button));
  GtkWidget *part_list_drop_down_button = gtk_widget_get_prev_sibling(button);
  GtkWidget *repl_list_drop_down_button =
      gtk_widget_get_prev_sibling(part_list_drop_down_button);
  repl_list_drop_down_button =
      gtk_widget_get_prev_sibling(repl_list_drop_down_button);
  char *repl_str_list = get_list_str_from_drop(repl_list_drop_down_button);
  char *part_str_list = get_list_str_from_drop(part_list_drop_down_button);
  if (str_amount[0] && str_time[0] && str_iterest_rate[0] && str_tax_rate[0]) {
    guint error = 0;
    error = check_str_amount_for_error(str_amount, error);
    error = check_str_time_for_error(str_time, error, id_depos_time);
    error = check_str_rate_for_error(str_iterest_rate, error);
    error = check_str_rate_for_error(str_tax_rate, error);
    GtkWidget *grid = gtk_widget_get_next_sibling(button);
    if (grid) {
      for (int i = 0; i < 3; i++) gtk_grid_remove_row(GTK_GRID(grid), 0);
    } else {
      grid = gtk_grid_new();
      grid_setings(grid, 10, 10, 10, -1, 50, 1);
      gtk_box_append(GTK_BOX(vbox), grid);
    }
    if (!error) {
      double result = 0;
      double tax_amount = 0;
      double amount = 0;
      calculate_depos(id_depos_time, str_amount, str_iterest_rate, str_tax_rate,
                      str_time, id_freq_pay, is_capitalization, &result,
                      &tax_amount, &amount, part_str_list, repl_str_list);
      print_depos_answer(grid, result, tax_amount, amount);
    } else {
      print_depos_error(grid, error);
    }
  }
  free(repl_str_list);
  free(part_str_list);
}

char *get_list_str_from_drop(GtkWidget *my_drop_down_button) {
  char *str_list = NULL;
  GtkPopover *popover =
      gtk_menu_button_get_popover(GTK_MENU_BUTTON(my_drop_down_button));
  GtkWidget *scrolled_win = gtk_popover_get_child(popover);
  GtkWidget *viewport =
      gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrolled_win));
  GtkWidget *vbox_popover = gtk_widget_get_first_child(viewport);
  GtkWidget *hbox = gtk_widget_get_first_child(vbox_popover);
  if (hbox) {
    str_list = calloc(1, sizeof(char));
    while (hbox) {
      GtkWidget *label = gtk_widget_get_first_child(hbox);
      const char *str = gtk_label_get_label(GTK_LABEL(label));
      char *buf = g_strconcat(str_list, str, NULL);
      free(str_list);
      str_list = buf;
      hbox = gtk_widget_get_next_sibling(hbox);
      if (hbox) {
        buf = g_strconcat(str_list, "|", NULL);
        free(str_list);
        str_list = buf;
      }
    }
  }
  return str_list;
}

void calculate_depos(guint id_depos_time, const char *str_amount,
                     const char *str_iterest_rate, const char *str_tax_rate,
                     const char *str_time, guint id_freq_pay,
                     gboolean is_capitalization, double *result,
                     double *tax_amount, double *amount, char *part_str_list,
                     char *repl_str_list) {
  time_t current_time = time(NULL);
  GDate *current_date = g_date_new();
  g_date_set_time_t(current_date, current_time);
  GDate *end_date = g_date_copy(current_date);
  GDate *buf_date = g_date_copy(current_date);
  guint n_time = 0;
  sscanf(str_time, "%u", &n_time);
  if (id_depos_time == 0)
    g_date_add_years(end_date, n_time);
  else if (id_depos_time == 1)
    g_date_add_months(end_date, n_time);
  else if (id_depos_time == 2)
    g_date_add_days(end_date, n_time);
  sscanf(str_amount, "%lf", amount);
  double iterest_rate = 0;
  sscanf(str_iterest_rate, "%lf", &iterest_rate);
  buf_date = take_next_date_for_pay(buf_date, id_freq_pay);
  double tax_rate = 0;
  sscanf(str_tax_rate, "%lf", &tax_rate);
  cycle_proc(current_date, amount, iterest_rate, result, id_freq_pay,
             is_capitalization, end_date, tax_amount, tax_rate, buf_date,
             part_str_list, repl_str_list);
  if (*tax_amount < 0) *tax_amount = 0;
  g_date_free(buf_date);
  g_date_free(end_date);
  g_date_free(current_date);
}

GDate *take_next_date_for_pay(GDate *buf_date, guint id_freq_pay) {
  if (id_freq_pay == 1)
    g_date_add_days(buf_date, 7);
  else if (id_freq_pay == 2)
    g_date_add_months(buf_date, 1);
  else if (id_freq_pay == 3)
    g_date_add_months(buf_date, 3);
  else if (id_freq_pay == 4)
    g_date_add_months(buf_date, 6);
  else if (id_freq_pay == 5)
    g_date_add_years(buf_date, 1);
  return buf_date;
}

void cycle_proc(GDate *current_date, double *amount, double iterest_rate,
                double *result, guint id_freq_pay, gboolean is_capitalization,
                GDate *end_date, double *tax_amount, double tax_rate,
                GDate *buf_date, char *part_str_list, char *repl_str_list) {
  double accrued_interest = 0;
  double res_for_tax = 0;
  while (g_date_compare(current_date, end_date)) {
    g_date_add_days(current_date, 1);
    guint number_day_at_year = 365;
    if (g_date_is_leap_year(g_date_get_year(current_date)))
      number_day_at_year = 366;
    double interest_for_day =
        *amount * (iterest_rate / 100.0) / number_day_at_year;
    *result += interest_for_day;
    if (id_freq_pay == 0) {
      *result -= interest_for_day;
      *result += round(interest_for_day * 100.0) / 100.0;
      res_for_tax += round(interest_for_day * 100.0) / 100.0;
      if (is_capitalization) *amount += round(interest_for_day * 100.0) / 100.0;
      if ((g_date_get_month(current_date) == 12 &&
           g_date_get_day(current_date) == 31) ||
          !g_date_compare(current_date, end_date)) {
        double buf = (res_for_tax - 75000) * (tax_rate / 100);
        if (buf > 0) *tax_amount += buf;
        res_for_tax = 0;
      }
    } else if (id_freq_pay == 6) {
      if (!g_date_compare(current_date, end_date)) {
        *result = round(*result * 100.0) / 100.0;
        *tax_amount = (*result - 75000) * (tax_rate / 100);
        if (is_capitalization) *amount += *result;
      }
    } else {
      accrued_interest += interest_for_day;
      if (!g_date_compare(current_date, buf_date) ||
          !g_date_compare(current_date, end_date)) {
        accrued_interest = round(accrued_interest * 100.0) / 100.0;
        *result = round(*result * 100.0) / 100.0;
        res_for_tax += accrued_interest;
        if (is_capitalization)
          *amount += round(accrued_interest * 100.0) / 100.0;
        accrued_interest = 0;
        buf_date = take_next_date_for_pay(buf_date, id_freq_pay);
      }
      if ((g_date_get_month(current_date) == 12 &&
           g_date_get_day(current_date) == 31) ||
          !g_date_compare(current_date, end_date)) {
        double buf = (res_for_tax - 75000) * (tax_rate / 100);
        if (buf > 0) *tax_amount += buf;
        res_for_tax = 0;
      }
    }
    *amount += correct_amount(repl_str_list, *current_date);
    *amount -= correct_amount(part_str_list, *current_date);
  }
}

double correct_amount(char *str_list, GDate current_date) {
  double answer = 0;
  if (str_list) {
    char **list_repl = g_strsplit(str_list, "|", -1);
    for (int i = 0; list_repl[i]; i++) {
      if (list_repl[i]) {
        char **data = g_strsplit(list_repl[i], "\t", -1);
        int day, month, year;
        sscanf(data[1], "%d.%d.%d", &day, &month, &year);
        GDate *date_for_check = g_date_new_dmy(day, month, year);
        if (data[0][7] == 'e') {
          if (!g_date_compare(&current_date, date_for_check)) {
            double number = 0;
            sscanf(data[2], "%lf", &number);
            answer += number;
          }
        } else if (data[0][7] == 'm') {
          if (g_date_compare(&current_date, date_for_check) >= 0) {
            if ((g_date_get_day(date_for_check) ==
                 g_date_get_day(&current_date)) ||
                (g_date_get_day(date_for_check) >
                     g_date_get_day(&current_date) &&
                 g_date_is_last_of_month(&current_date))) {
              double number = 0;
              sscanf(data[2], "%lf", &number);
              answer += number;
            }
          }
        } else if (data[0][7] == 'y') {
          if (g_date_compare(&current_date, date_for_check) >= 0) {
            if ((day == 29 && month == 2 &&
                 !g_date_is_leap_year(g_date_get_year(&current_date)) &&
                 current_date.day == 1 && current_date.month == 3) ||
                (day == current_date.day && month == current_date.month)) {
              double number = 0;
              sscanf(data[2], "%lf", &number);
              answer += number;
            }
          }
        }
        g_date_free(date_for_check);
        g_strfreev(data);
      }
    }
    g_strfreev(list_repl);
  }
  return answer;
}

void print_depos_answer(GtkWidget *grid, double result, double tax_amount,
                        double amount) {
  char str_result[1024] = {0};
  sprintf(str_result, "%.2f", result);
  char str_tax_amount[1024] = {0};
  sprintf(str_tax_amount, "%.2f", tax_amount);
  char str_amount[1024] = {0};
  sprintf(str_amount, "%.2f", amount);
  GtkWidget *label_result_name =
      gtk_label_new_with_mnemonic("Accrued interest");
  gtk_grid_attach(GTK_GRID(grid), label_result_name, 0, 0, 1, 1);
  GtkWidget *label_result = gtk_label_new_with_mnemonic(str_result);
  gtk_grid_attach(GTK_GRID(grid), label_result, 1, 0, 1, 1);
  GtkWidget *label_tax_name = gtk_label_new_with_mnemonic("Tax");
  gtk_grid_attach(GTK_GRID(grid), label_tax_name, 0, 1, 1, 1);
  GtkWidget *label_tax = gtk_label_new_with_mnemonic(str_tax_amount);
  gtk_grid_attach(GTK_GRID(grid), label_tax, 1, 1, 1, 1);
  GtkWidget *label_amount_name = gtk_label_new_with_mnemonic("Deposit amount");
  gtk_grid_attach(GTK_GRID(grid), label_amount_name, 0, 2, 1, 1);
  GtkWidget *label_amount = gtk_label_new_with_mnemonic(str_amount);
  gtk_grid_attach(GTK_GRID(grid), label_amount, 1, 2, 1, 1);
}

void print_depos_error(GtkWidget *grid, guint error) {
  GtkWidget *label_1 = gtk_label_new(NULL);
  if (error == 1)
    gtk_label_set_markup(
        GTK_LABEL(label_1),
        "<span color=\"red\">*AMOUNT OF DEPOSIT can be in the "
        "format\n\"999.99\". The minimum allowed value is 1.</span>");
  else if (error == 2)
    gtk_label_set_markup(
        GTK_LABEL(label_1),
        "<span color=\"red\">*DEPOSIT TIME must be an integer in the "
        "range\nfrom 1 to 50 for \"yeara\",  from 1 to 600\nfor \"month\" and "
        "from 1 to 18250 for \"days\".</span>");
  else if (error == 3)
    gtk_label_set_markup(
        GTK_LABEL(label_1),
        "<span color=\"red\">*RATE must be between 0.01 and 999.</span>");
  gtk_widget_set_halign(label_1, GTK_ALIGN_START);
  gtk_grid_attach(GTK_GRID(grid), label_1, 0, 0, 1, 1);
}