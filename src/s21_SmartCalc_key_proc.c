#include "s21_SmartCalc.h"

void set_button_for_calc(GtkWidget *vbox, GtkWidget *hbox6, char ch) {
  GtkWidget *grid = gtk_grid_new();
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(vbox), grid);
  char names_button[35][5] = {"x",
                              "atan",
                              "tan",
                              "ln",
                              "log",
                              {-16, -99, -99, -123, 0},
                              "sqrt",
                              "^",
                              "C",
                              {-30, -116, -85, 0, 0},
                              "abs",
                              "(",
                              ")",
                              "mod",
                              {-61, -73, 0, 0, 0},
                              "acos",
                              "7",
                              "8",
                              "9",
                              {-61, -105, 0, 0, 0},
                              "cos",
                              "4",
                              "5",
                              "6",
                              "-",
                              "asin",
                              "1",
                              "2",
                              "3",
                              "+",
                              "sin",
                              "+/-",
                              "0",
                              ".",
                              "="};
  GtkWidget *button, *label;
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 5; j++) {
      button = gtk_button_new();
      label = gtk_label_new(NULL);
      char s[1024] = {0};
      sprintf(s, "%s%s%s", SET_SIZE_BEGIN, names_button[j + i * 5],
              SET_SIZE_END);
      gtk_label_set_markup(GTK_LABEL(label), s);
      gtk_button_set_child(GTK_BUTTON(button), label);
      gtk_widget_set_size_request(button, 65, 50);
      if (ch == 'm')
        g_signal_connect(button, "clicked", G_CALLBACK(click_button), grid);
      else
        g_signal_connect(button, "clicked", G_CALLBACK(click_button), hbox6);
      gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);
    }
}

void click_button(GtkWidget *button, gpointer grid) {
  GtkWidget *label_button = gtk_button_get_child(GTK_BUTTON(button));
  const char *name_button = gtk_label_get_label(GTK_LABEL(label_button));
  int key = name_button[19];
  GtkWidget *label_entry = gtk_widget_get_prev_sibling(grid);
  if (key == -30 && name_button[20] == -116 && name_button[21] == -85)
    key = 65288;
  if (key == 'm') key = '%';
  if (key == 's' && name_button[20] == 'q') key = '@';
  if (key == -61 && name_button[20] == -73) key = '/';
  if (key == -61 && name_button[20] == -105) key = '*';
  if (key == 'C') {
    key_pressed(label_entry, key, 'l', 0);
  } else if (key == '+' && name_button[20] == '/' && name_button[21] == '-') {
    save_extended_operation(label_entry, "negate");
  } else if (key == 'l' && name_button[20] == 'n') {
    save_extended_operation(label_entry, "ln");
  } else if (key == 'l' && name_button[20] == 'o') {
    save_extended_operation(label_entry, "log");
  } else if (key == 't') {
    save_extended_operation(label_entry, "tan");
  } else if (key == 'a' && name_button[20] == 't') {
    save_extended_operation(label_entry, "atan");
  } else if (key == 'e') {
    save_extended_operation(label_entry, "exp");
  } else if (key == -16 && name_button[20] == -99 && name_button[21] == -99) {
    save_extended_operation(label_entry, "pi");
  } else if (key == 'a' && name_button[20] == 'b') {
    save_extended_operation(label_entry, "abs");
  } else if (key == 'a' && name_button[20] == 'c') {
    save_extended_operation(label_entry, "acos");
  } else if (key == 'c') {
    save_extended_operation(label_entry, "cos");
  } else if (key == 'a' && name_button[20] == 's') {
    save_extended_operation(label_entry, "asin");
  } else if (key == 's' && name_button[20] == 'i') {
    save_extended_operation(label_entry, "sin");
  } else {
    key_pressed(label_entry, key, 0, 0);
  }
}

gboolean key_pressed(GtkWidget *label_entry, guint keyval, guint keycode,
                     GdkModifierType state) {
  gboolean answer = TRUE;
  guint key = keyval;
  if (key == ',') key = '.';
  static gboolean pointer = FALSE;
  static guint count_number_after_point = 0;
  static guint count_bracket = 0;
  static gboolean pressed_x = FALSE;
  static gboolean must_set_x = FALSE;
  static gboolean set_x = FALSE;
  GtkWidget *prev_label_entry = gtk_widget_get_prev_sibling(label_entry);
  if (key == 'C' && keycode == 'l') {
    gtk_label_set_label(GTK_LABEL(label_entry), "<span size=\"300%\">0</span>");
    gtk_label_set_label(GTK_LABEL(prev_label_entry), NULL);
    pointer = FALSE;
    count_number_after_point = 0;
    count_bracket = 0;
    pressed_x = FALSE;
    must_set_x = FALSE;
    set_x = FALSE;
  }
  const char *menu_name = get_name_button_menu(prev_label_entry);
  if (key == 'x' && menu_name[0] == 'M') {
    pressed_x = TRUE;
    must_set_x = TRUE;
  }
  if (state & (GDK_CONTROL_MASK | GDK_ALT_MASK)) answer = FALSE;
  if ((key >= 65453 && key <= 65465) || key == 65450 || key == 65451)
    key = key - 65408;
  if (!pressed_x && answer && (key >= '0' && key <= '9'))
    print_number(label_entry, prev_label_entry, key, &pointer, set_x);
  if (answer && ((key == '.' && !pointer) || key == 'x'))
    print_number(label_entry, prev_label_entry, key, &pointer, set_x);
  if (key == '.') pointer = TRUE;
  if (answer && key == 65288) {
    if (pressed_x) pressed_x = FALSE;
    guint last_char = del_last_char(label_entry);
    if (last_char == ')') count_bracket++;
    if (last_char == '(') count_bracket--;
    if (pointer && count_number_after_point > 0) count_number_after_point--;
    if (count_number_after_point == 0) pointer = FALSE;
  }
  if (!set_x && answer &&
      (key == '%' || key == '(' || (key == ')' && count_bracket > 0) ||
       key == '*' || key == '+' || key == '-' || key == '/' ||
       (key == '=' && count_bracket == 0) || key == '@' || key == '^')) {
    answer = !(save_operation(label_entry, key));
    pointer = FALSE;
    pressed_x = FALSE;
    count_number_after_point = 0;
  }
  if (answer && key == '=' && count_bracket == 0 && menu_name[0] == 'M')
    proc_for_main_calc(prev_label_entry, label_entry, &set_x, &must_set_x,
                       &pointer);
  if (answer && key == '=' && count_bracket == 0 && menu_name[0] == 'P')
    proc_for_ploting_calc(prev_label_entry, label_entry);
  if (key == '(') count_bracket++;
  if (key == ')' && count_bracket > 0) count_bracket--;
  return answer;
}

const char *get_name_button_menu(GtkWidget *prev_label_entry) {
  GtkWidget *hbox = gtk_widget_get_prev_sibling(prev_label_entry);
  GtkWidget *menu_button = gtk_widget_get_first_child(hbox);
  GtkWidget *hbox2 = gtk_widget_get_next_sibling(menu_button);
  GtkWidget *label = gtk_widget_get_first_child(hbox2);
  const char *s = gtk_label_get_label(GTK_LABEL(label));
  return s;
}

void print_number(GtkWidget *label_entry, GtkWidget *prev_label_entry,
                  guint key, gboolean *pointer, gboolean set_x) {
  const char *buf_prev_label = gtk_label_get_text(GTK_LABEL(prev_label_entry));
  int len = strlen(buf_prev_label);
  if (buf_prev_label[0] != '\0') {
    if (buf_prev_label[len - 1] == '=') {
      if (!set_x) {
        gtk_label_set_label(GTK_LABEL(prev_label_entry), "\0");
        gtk_label_set_label(GTK_LABEL(label_entry),
                            "<span size=\"300%\">0</span>");
        *pointer = FALSE;
      }
    }
  }
  const char *buf_label = gtk_label_get_label(GTK_LABEL(label_entry));
  char label_string[1024] = {0};
  if (buf_label[18] == '0') {
    sprintf(label_string, "%s%c%s", SET_SIZE_BEGIN_300, key, SET_SIZE_END);
  } else {
    char new_label[512] = {0};
    cut_label(buf_label, new_label);
    if (key != 'x') {
      sprintf(label_string, "%s%s%c%s", SET_SIZE_BEGIN_300, new_label, key,
              SET_SIZE_END);
    } else {
      sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300, new_label,
              SET_SIZE_END);
    }
  }
  gtk_label_set_markup(GTK_LABEL(label_entry), label_string);
}

int cut_label(const char *buf_label, char *new_label) {
  int i = 18;
  int j = 0;
  while (buf_label[i] != '<') new_label[j++] = buf_label[i++];
  return j;
}

gboolean save_operation(GtkWidget *label_entry, guint key) {
  GtkWidget *prev_label_entry = gtk_widget_get_prev_sibling(label_entry);
  const char *buf_label = gtk_label_get_label(GTK_LABEL(label_entry));
  const char *buf_prev_label = gtk_label_get_label(GTK_LABEL(prev_label_entry));
  gboolean error = FALSE;
  char label_string[1024] = {0};
  char new_label[512] = {0};
  cut_label(buf_label, new_label);
  if (buf_prev_label[0] == '\0') {
    concat_label_1(key, new_label, label_string);
  } else {
    char new_label_prev[512] = {0};
    int len = cut_label(buf_prev_label, new_label_prev);
    if (len + 4 > 512) {
      label_string[0] = '=';
      error = TRUE;
    } else {
      if (new_label_prev[len - 1] == '=')
        for (int i = 0; i < len; i++) new_label_prev[i] = '\0';
      if (new_label_prev[len - 1] == ' ') {
        new_label_prev[len - 1] = '\0';
        len--;
      }
      if (new_label_prev[len - 1] >= '0' && new_label_prev[len - 1] <= '9')
        concat_label_2(key, new_label, new_label_prev, label_string,
                       buf_label[18]);
      else if (new_label_prev[len - 1] == ')')
        concat_label_3(key, new_label_prev, label_string);
      else
        concat_label_4(key, new_label, new_label_prev, label_string,
                       buf_label[18], len);
    }
  }
  gtk_label_set_markup(GTK_LABEL(prev_label_entry), label_string);
  if (error)
    gtk_label_set_markup(GTK_LABEL(label_entry),
                         "<span size=\"300%\">ERROR</span>");
  else
    gtk_label_set_markup(GTK_LABEL(label_entry),
                         "<span size=\"300%\">0</span>");
  return error;
}

char *concat_label_1(guint key, char *new_label, char *label_string) {
  if (key == '%')
    sprintf(label_string, "%s%s %s%s", SET_SIZE_BEGIN_100, new_label, "mod",
            SET_SIZE_END);
  else if (key == '@')
    sprintf(label_string, "%s%s%s%c%s", SET_SIZE_BEGIN_100, "sqrt(", new_label,
            ')', SET_SIZE_END);
  else if (key == '(')
    sprintf(label_string, "%s%c%s", SET_SIZE_BEGIN_100, key, SET_SIZE_END);
  else
    sprintf(label_string, "%s%s %c%s", SET_SIZE_BEGIN_100, new_label, key,
            SET_SIZE_END);
  return label_string;
}

char *concat_label_2(guint key, char *new_label, char *new_label_prev,
                     char *label_string, char buf) {
  if (key == '%')
    sprintf(label_string, "%s%s%s %s%s", SET_SIZE_BEGIN_100, new_label_prev,
            new_label, "mod", SET_SIZE_END);
  else if (key == '@')
    sprintf(label_string, "%s%s%s%s%c%s", SET_SIZE_BEGIN_100, new_label_prev,
            "sqrt(", new_label, ')', SET_SIZE_END);
  else if (key == '(')
    sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_100, new_label_prev,
            SET_SIZE_END);
  else if (buf == '0')
    sprintf(label_string, "%s%s %c%s", SET_SIZE_BEGIN_100, new_label_prev, key,
            SET_SIZE_END);
  else
    sprintf(label_string, "%s%s%s %c%s", SET_SIZE_BEGIN_100, new_label_prev,
            new_label, key, SET_SIZE_END);
  return label_string;
}

char *concat_label_3(guint key, char *new_label_prev, char *label_string) {
  if (key != '@' && key != '%') {
    if (key == ')')
      sprintf(label_string, "%s%s%c%s", SET_SIZE_BEGIN_100, new_label_prev, key,
              SET_SIZE_END);
    else
      sprintf(label_string, "%s%s %c%s", SET_SIZE_BEGIN_100, new_label_prev,
              key, SET_SIZE_END);
  } else if (key == '%') {
    sprintf(label_string, "%s%s %s%s", SET_SIZE_BEGIN_100, new_label_prev,
            "mod", SET_SIZE_END);
  } else {
    sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_100, new_label_prev,
            SET_SIZE_END);
  }
  return label_string;
}

char *concat_label_4(guint key, char *new_label, char *new_label_prev,
                     char *label_string, char buf, int len) {
  if (key == '%')
    sprintf(label_string, "%s%s %s %s%s", SET_SIZE_BEGIN_100, new_label_prev,
            new_label, "mod", SET_SIZE_END);
  else if (key == '@')
    sprintf(label_string, "%s%s %s%s%c%s", SET_SIZE_BEGIN_100, new_label_prev,
            "sqrt(", new_label, ')', SET_SIZE_END);
  else if (key == '(')
    if (new_label_prev[len - 1] == '(')
      sprintf(label_string, "%s%s%c%s", SET_SIZE_BEGIN_100, new_label_prev, key,
              SET_SIZE_END);
    else
      sprintf(label_string, "%s%s %c%s", SET_SIZE_BEGIN_100, new_label_prev,
              key, SET_SIZE_END);
  else if (buf == 0)
    sprintf(label_string, "%s%s %c%s", SET_SIZE_BEGIN_100, new_label_prev, key,
            SET_SIZE_END);
  else
    sprintf(label_string, "%s%s %s %c%s", SET_SIZE_BEGIN_100, new_label_prev,
            new_label, key, SET_SIZE_END);
  return label_string;
}

guint del_last_char(GtkWidget *label_entry) {
  guint last_char = 0;
  const char *buf_label = gtk_label_get_label(GTK_LABEL(label_entry));
  if (buf_label[18] != '0') {
    char label_string[1024] = {0};
    char new_label[512] = {0};
    int len = cut_label(buf_label, new_label);
    if (new_label[len - 1] != ' ') {
      last_char = new_label[len - 1];
      new_label[len - 1] = '\0';
    }
    if (buf_label[19] == '<')
      sprintf(label_string, "%s%c%s", SET_SIZE_BEGIN_300, '0', SET_SIZE_END);
    else
      sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300, new_label,
              SET_SIZE_END);
    gtk_label_set_markup(GTK_LABEL(label_entry), label_string);
  } else {
    GtkWidget *prev_label_entry = gtk_widget_get_prev_sibling(label_entry);
    const char *buf_prev_label =
        gtk_label_get_label(GTK_LABEL(prev_label_entry));
    if (buf_prev_label[0] != '\0') {
      char label_string[1024] = {0};
      char new_label[512] = {0};
      int i = 18;
      int j = 0;
      while (buf_prev_label[i] != '<') new_label[j++] = buf_prev_label[i++];
      last_char = new_label[j - 1];
      new_label[j - 1] = '\0';
      if (last_char == ')') new_label[j - 2] = '\0';
      if (buf_prev_label[19] == '<') {
        gtk_label_set_label(GTK_LABEL(prev_label_entry), NULL);
      } else {
        sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_100, new_label,
                SET_SIZE_END);
        gtk_label_set_markup(GTK_LABEL(prev_label_entry), label_string);
      }
    }
  }
  return last_char;
}

void save_extended_operation(GtkWidget *label_entry, char *function) {
  GtkWidget *prev_label_entry = gtk_widget_get_prev_sibling(label_entry);
  const char *buf_label = gtk_label_get_label(GTK_LABEL(label_entry));
  const char *buf_prev_label = gtk_label_get_label(GTK_LABEL(prev_label_entry));
  char label_string[1024] = {0};
  char new_label[512] = {0};
  cut_label(buf_label, new_label);
  if (new_label[0] != 's') {
    if (function[0] == 'n') {
      if (new_label[0] != '-')
        sprintf(label_string, "%s%c%s%s", SET_SIZE_BEGIN_300, '-', new_label,
                SET_SIZE_END);
      else
        sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300, &new_label[1],
                SET_SIZE_END);
    } else if (function[0] == 'p') {
      if (new_label[0] == 's')
        sprintf(label_string, "%s%s%.10f%s", SET_SIZE_BEGIN_300,
                "set value x: ", G_PI, SET_SIZE_END);
      else
        sprintf(label_string, "%s%.10f%s", SET_SIZE_BEGIN_300, G_PI,
                SET_SIZE_END);
    } else {
      if (new_label[0] == 's')
        sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300,
                "set value x: ", SET_SIZE_END);
      else
        sprintf(label_string, "%s%d%s", SET_SIZE_BEGIN_300, 0, SET_SIZE_END);
      char label_prev_string[1024] = {0};
      if (buf_prev_label[0] == '\0') {
        sprintf(label_prev_string, "%s%s%c%s%c%s", SET_SIZE_BEGIN_100, function,
                '(', new_label, ')', SET_SIZE_END);
      } else {
        char new_label_prev[256] = {0};
        int len = cut_label(buf_prev_label, new_label_prev);
        if (new_label_prev[len - 1] == '-' || new_label_prev[len - 1] == '+' ||
            new_label_prev[len - 1] == '*' || new_label_prev[len - 1] == '/' ||
            new_label_prev[len - 1] == 'd' || new_label_prev[len - 1] == '(' ||
            new_label_prev[len - 1] == '^') {
          sprintf(label_prev_string, "%s%s %s%c%s%c%s", SET_SIZE_BEGIN_100,
                  new_label_prev, function, '(', new_label, ')', SET_SIZE_END);
        } else if (new_label_prev[len - 1] == '=') {
          sprintf(label_prev_string, "%s%s%c%s%c%s", SET_SIZE_BEGIN_100,
                  function, '(', new_label, ')', SET_SIZE_END);
        } else {
          sprintf(label_prev_string, "%s%s%s", SET_SIZE_BEGIN_100,
                  new_label_prev, SET_SIZE_END);
        }
      }
      gtk_label_set_markup(GTK_LABEL(prev_label_entry), label_prev_string);
    }
  } else {
    if (function[0] == 'p')
      sprintf(label_string, "%s%s%.10f%s", SET_SIZE_BEGIN_300,
              "set value x: ", G_PI, SET_SIZE_END);
    else if (function[0] == 'n')
      if (new_label[13] == '-' || new_label[13] == '\0')
        sprintf(label_string, "%s%s%s%s", SET_SIZE_BEGIN_300,
                "set value x: ", &new_label[13], SET_SIZE_END);
      else
        sprintf(label_string, "%s%s%c%s%s", SET_SIZE_BEGIN_300,
                "set value x: ", '-', &new_label[13], SET_SIZE_END);
    else
      sprintf(label_string, "%s%s%s", SET_SIZE_BEGIN_300,
              "set value x: ", SET_SIZE_END);
  }
  gtk_label_set_markup(GTK_LABEL(label_entry), label_string);
}