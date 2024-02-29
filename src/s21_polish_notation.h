#ifndef S21_POLISH_NOTATION_
#define S21_POLISH_NOTATION_

#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct keys_check {
  guint is_number;
  guint is_function;
  guint is_operator;
  guint is_bkt_cls;
} KeysCheck;

GSList *polish_notation(char *str, GSList *result, guint *error);
double polish_calc(GSList *polish_list, char *value_x);
guint is_operator(char *data);
GSList *put_to_list_result(GSList *number, char *data);
GSList *get_one_number(GSList *number_lst, double *number);
GSList *get_two_number(GSList *number, double *number_1, double *number_2);
guint operation_priority(char *str);
guint function_check(char *ptr, char *str_copy);
void check_word(char *ptr, char *str, guint *error);
char *add_to_string(char *put_str, char *ptr, char lexeme_type,
                    guint *len_put_str);
guint is_lexeme_type(char ptr, char lexeme_type);
guint checking_str_for_err(char *str);
void reset_keys(KeysCheck *keys);
guint operator_proc(char *ptr, GSList **result, GSList **stack,
                    KeysCheck *keys);
void bracket_proc(GSList **result, GSList **stack, guint *error);
GSList *pop_from_list(GSList *stack);
GSList *put_to_result(GSList *tmp, GSList *result, guint *error);

#endif  // S21_POLISH_NOTATION_