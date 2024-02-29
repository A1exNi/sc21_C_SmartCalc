#ifndef S21_SMART_CALC_H_
#define S21_SMART_CALC_H_

#include <gtk/gtk.h>
#include <math.h>
#include <time.h>

#include "s21_polish_notation.h"

#define SET_SIZE_BEGIN "<span size=\"large\">"
#define SET_SIZE_BEGIN_300 "<span size=\"300%\">"
#define SET_SIZE_BEGIN_170 "<span size=\"170%\">"
#define SET_SIZE_BEGIN_120 "<span size=\"120%\">"
#define SET_SIZE_BEGIN_100 "<span size=\"100%\">"
#define SET_SIZE_END "</span>"

void activate(GtkApplication *app);
void main_calc(gpointer window);
GtkWidget *set_menu(int row);
void set_button_for_calc(GtkWidget *grid, GtkWidget *hbox6, char ch);
void click_button(GtkWidget *button, gpointer grid);
gboolean key_pressed(GtkWidget *label_entry, guint keyval, guint keycode,
                     GdkModifierType state);
const char *get_name_button_menu(GtkWidget *prev_label_entry);
void print_number(GtkWidget *label_entry, GtkWidget *prev_label_entry,
                  guint key, gboolean *pointer, gboolean set_x);
int cut_label(const char *buf_label, char *new_label);
gboolean save_operation(GtkWidget *label_entry, guint key);
char *concat_label_1(guint key, char *new_label, char *label_string);
char *concat_label_2(guint key, char *new_label, char *new_label_prev,
                     char *label_string, char buf);
char *concat_label_3(guint key, char *new_label_prev, char *label_string);
char *concat_label_4(guint key, char *new_label, char *new_label_prev,
                     char *label_string, char buf, int len);
guint del_last_char(GtkWidget *label_entry);
void save_extended_operation(GtkWidget *label_entry, char *function);
void proc_for_main_calc(GtkWidget *prev_label_entry, GtkWidget *label_entry,
                        gboolean *set_x, gboolean *must_set_x,
                        gboolean *pointer);
gboolean have_x(const char *str);
double result_calculation(char *x, char *expression, guint *error);
void window_select(GtkWidget *list_box);
void grid_credit_fill(GtkWidget *grid);
void credit_calc(gpointer window);
void grid_setings(GtkWidget *grid, int margin_start, int margin_top,
                  int margin_end, int margin_bottom, int column_spacing,
                  int row_spacing);
void proc_credit(GtkWidget *button, gpointer vbox);
void calculate_credit(const char *str_amount, const char *str_time,
                      const char *str_rate, guint id_drop_down,
                      gboolean is_annuity, char **str_list_mon_pay,
                      double *mon_pay, double *total_pay, double *over_pay);
void print_answer(GtkWidget *grid, double mon_pay, double total_pay,
                  double over_pay, char *str_list_mon_pay, gboolean is_annuity);
void print_error(GtkWidget *grid, guint error);
guint check_str_amount_for_error(const char *str_amount, guint error);
guint check_str_time_for_error(const char *str_time, guint error,
                               guint id_drop_down);
guint check_str_rate_for_error(const char *str_rate, guint error);
void depos_calc(gpointer window);
void grid_depos_fill(GtkWidget *grid);
void add_list(GtkWidget *vbox, char *name_label);
GtkWidget *my_drop_down_button(GtkWidget *vbox, char *name_label);
void add_list_button(GtkWidget *button, gpointer vbox_popover_for_list);
GtkWidget *get_button_in_depos(GtkWidget *vbox);
void add_data_to_drop_depos(char *drop_str, const char *date_str,
                            const char *amount_str,
                            gpointer vbox_popover_for_list);
void del_row_from_list(GtkWidget *button_del, gpointer vbox);
void proc_depos(GtkWidget *button, gpointer vbox);
char *get_list_str_from_drop(GtkWidget *my_drop_down_button);
void calculate_depos(guint id_depos_time, const char *str_amount,
                     const char *str_iterest_rate, const char *str_tax_rate,
                     const char *str_time, guint id_freq_pay,
                     gboolean is_capitalization, double *result,
                     double *tax_amount, double *amount, char *part_str_list,
                     char *repl_str_list);
GDate *take_next_date_for_pay(GDate *buf_date, guint id_freq_pay);
void cycle_proc(GDate *current_date, double *amount, double iterest_rate,
                double *result, guint id_freq_pay, gboolean is_capitalization,
                GDate *end_date, double *tax_amount, double tax_rate,
                GDate *buf_date, char *part_str_list, char *repl_str_list);
double correct_amount(char *str_list, GDate current_date);
void print_depos_answer(GtkWidget *grid, double result, double tax_amount,
                        double amount);
void print_depos_error(GtkWidget *grid, guint error);
guint count_number_from_str(char *ptr, guint *error);
guint check_str_date_for_error(const char *date_str, guint error);
void plot_calc(gpointer window, gboolean activ, char *expression,
               int minmax_buf[4], gboolean print_e);
void set_plot_window(GtkWidget *button, gpointer minmax);
void calc_y(double *data, char *expression, guint *error);
void draw_calc(GtkWidget *vbox, int minmax[4], gboolean print_e);
void draw_area(GtkDrawingArea *area, cairo_t *cr, int width, int height,
               gpointer data);
void draw_arrow(cairo_t *cr, double cx, double cy, int width, int height);
void draw_grid_x(cairo_t *cr, double cx, double cy, double max_x, double min_x,
                 int width, int height, double indent_x);
void draw_grid_y(cairo_t *cr, double cx, double cy, double max_y, double min_y,
                 int width, int height, double indent_y);
void proc_for_ploting_calc(GtkWidget *prev_label_entry, GtkWidget *label_entry);
void func_error(guint error, GtkWidget *grid);

#endif  // S21_SMART_CALC_H_