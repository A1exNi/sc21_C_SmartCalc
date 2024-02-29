#include "s21_SmartCalc.h"

void main_calc(gpointer window) {
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 33);
  gtk_window_set_child(window, vbox);
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  gtk_box_append(GTK_BOX(vbox), hbox);
  GtkWidget *menu = set_menu(0);
  gtk_box_append(GTK_BOX(hbox), menu);
  GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  gtk_box_append(GTK_BOX(hbox), hbox2);
  GtkWidget *name_menu = gtk_label_new_with_mnemonic("Main Calcuator");
  gtk_box_append(GTK_BOX(hbox2), name_menu);
  GtkWidget *label_entry = gtk_label_new(NULL);
  gtk_label_set_ellipsize(GTK_LABEL(label_entry), PANGO_ELLIPSIZE_START);
  gtk_label_set_xalign(GTK_LABEL(label_entry), 1);
  gtk_widget_set_margin_end(label_entry, 10);
  gtk_box_append(GTK_BOX(vbox), label_entry);
  label_entry = gtk_label_new(NULL);
  gtk_widget_set_margin_end(label_entry, 10);
  gtk_label_set_xalign(GTK_LABEL(label_entry), 1);
  gtk_label_set_ellipsize(GTK_LABEL(label_entry), PANGO_ELLIPSIZE_START);
  char label_string[1024] = {0};
  sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300, "0", SET_SIZE_END);
  gtk_label_set_markup(GTK_LABEL(label_entry), label_string);
  gtk_box_append(GTK_BOX(vbox), label_entry);
  GtkEventController *control_key = gtk_event_controller_key_new();
  g_signal_connect_swapped(control_key, "key-pressed", G_CALLBACK(key_pressed),
                           label_entry);
  gtk_widget_add_controller(vbox, control_key);
  set_button_for_calc(vbox, NULL, 'm');
  gtk_window_present(GTK_WINDOW(window));
}

void proc_for_main_calc(GtkWidget *prev_label_entry, GtkWidget *label_entry,
                        gboolean *set_x, gboolean *must_set_x,
                        gboolean *pointer) {
  char label_string[1024] = {0};
  const char *str_prev_label = gtk_label_get_label(GTK_LABEL(prev_label_entry));
  if (have_x(str_prev_label) && !(*set_x)) {
    sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300,
            "set value x: ", SET_SIZE_END);
    *must_set_x = FALSE;
    *set_x = TRUE;
  } else {
    const char *buf = gtk_label_get_label(GTK_LABEL(prev_label_entry));
    char expression[550] = {0};
    int len = cut_label(buf, expression);
    expression[len - 2] = '\0';
    if (*set_x) {
      char new_label[512] = {0};
      const char *buf_label = gtk_label_get_label(GTK_LABEL(label_entry));
      len = cut_label(buf_label, new_label);
      if (new_label[len - 1] != ' ') {
        char *cut_new_label = new_label + 13;
        guint error = 0;
        double result = result_calculation(cut_new_label, expression, &error);
        if (error)
          sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300, "ERROR",
                  SET_SIZE_END);
        else {
          sprintf(label_string, "%s%.9f%s", SET_SIZE_BEGIN_300, result,
                  SET_SIZE_END);
          *pointer = TRUE;
        }
      } else {
        sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300,
                "set value x: ", SET_SIZE_END);
      }
      *set_x = FALSE;
    } else {
      guint error = 0;
      double result = result_calculation(NULL, expression, &error);
      if (error) {
        sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300, "ERROR",
                SET_SIZE_END);
      } else {
        sprintf(label_string, "%s%.9f%s", SET_SIZE_BEGIN_300, result,
                SET_SIZE_END);
        *pointer = TRUE;
      }
    }
  }
  gtk_label_set_label(GTK_LABEL(label_entry), label_string);
}

gboolean have_x(const char *str) {
  gboolean answer = FALSE;
  for (char *ptr = (char *)str; *ptr && !answer; ptr++) {
    if (*ptr == 'x') answer = TRUE;
  }
  return answer;
}

double result_calculation(char *x, char *expression, guint *error) {
  double answer = 0;
  GSList *polish_list = NULL;
  polish_list = polish_notation(expression, polish_list, error);
  if (!(*error)) answer = polish_calc(polish_list, x);
  g_slist_free_full(polish_list, free);
  return answer;
}