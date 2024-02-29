#include "s21_polish_notation.h"

double polish_calc(GSList *polish_list, char *value_x) {
  double answer = 0;
  GSList *tmp = polish_list;
  GSList *number_list = NULL;
  while (tmp) {
    if ((((char *)tmp->data)[0] >= '0' && ((char *)tmp->data)[0] <= '9')) {
      number_list = g_slist_prepend(number_list, g_strdup((char *)tmp->data));
    } else if (((char *)tmp->data)[0] == 'x') {
      for (char *ptr = value_x; *ptr; ptr++)
        if (*ptr == '.') *ptr = ',';
      number_list = g_slist_prepend(number_list, g_strdup(value_x));
    } else {
      number_list = put_to_list_result(number_list, (char *)tmp->data);
    }
    tmp = g_slist_next(tmp);
  }
  get_one_number(number_list, &answer);
  return answer;
}

GSList *put_to_list_result(GSList *number_list, char *data) {
  double number_1 = 0;
  double number_2 = 0;
  if (is_operator(data))
    number_list = get_two_number(number_list, &number_1, &number_2);
  else
    number_list = get_one_number(number_list, &number_1);
  char number_str[1024] = {0};
  if (data[0] == '+')
    sprintf(number_str, "%.17lf", number_1 + number_2);
  else if (data[0] == '~')
    sprintf(number_str, "%.17lf", number_1 * (-1));
  else if (data[0] == '-')
    sprintf(number_str, "%.17lf", number_1 - number_2);
  else if (data[0] == '*')
    sprintf(number_str, "%.17lf", number_1 * number_2);
  else if (data[0] == '/')
    sprintf(number_str, "%.17lf", number_1 / number_2);
  else if (data[0] == '%')
    sprintf(number_str, "%.17lf", fmod(number_1, number_2));
  else if (data[0] == '^')
    sprintf(number_str, "%.17lf", pow(number_1, number_2));
  else if (data[0] == 'c')
    sprintf(number_str, "%.17lf", cos(number_1));
  else if (data[0] == 's' && data[1] == 'i')
    sprintf(number_str, "%.17lf", sin(number_1));
  else if (data[0] == 't')
    sprintf(number_str, "%.17lf", tan(number_1));
  else if (data[0] == 'a' && data[1] == 'c')
    sprintf(number_str, "%.17lf", acos(number_1));
  else if (data[0] == 'a' && data[1] == 's')
    sprintf(number_str, "%.17lf", asin(number_1));
  else if (data[0] == 'a' && data[1] == 't')
    sprintf(number_str, "%.17lf", atan(number_1));
  else if (data[0] == 's' && data[1] == 'q')
    sprintf(number_str, "%.17lf", sqrt(number_1));
  else if (data[0] == 'l' && data[1] == 'n')
    sprintf(number_str, "%.17lf", log(number_1));
  else if (data[0] == 'l' && data[1] == 'o')
    sprintf(number_str, "%.17lf", log10(number_1));
  else if (data[0] == 'n')
    sprintf(number_str, "%.17lf", number_1 * -1.0);
  else if (data[0] == 'a' && data[1] == 'b')
    sprintf(number_str, "%.17lf", fabs(number_1));
  number_list = g_slist_prepend(number_list, g_strdup(number_str));
  return number_list;
}

guint is_operator(char *data) {
  guint answer = 0;
  if (data[0] == '+' || data[0] == '-' || data[0] == '*' || data[0] == '/' ||
      data[0] == '%' || data[0] == '^')
    answer = 1;
  return answer;
}

GSList *get_two_number(GSList *number_lst, double *number_1, double *number_2) {
  number_lst = get_one_number(number_lst, number_2);
  if (number_lst) number_lst = get_one_number(number_lst, number_1);
  return number_lst;
}

GSList *get_one_number(GSList *number_lst, double *number) {
  sscanf((char *)number_lst->data, "%lf", number);
  GSList *tmp = number_lst;
  number_lst = g_slist_next(number_lst);
  free(tmp->data);
  g_slist_free_1(tmp);
  return number_lst;
}

GSList *polish_notation(char *str, GSList *result, guint *error) {
  *error = checking_str_for_err(str);
  char *str_copy = g_strdup(str);
  // guint len_put_str = 0;
  char *put_str = NULL;
  GSList *stack = NULL;
  KeysCheck keys;
  reset_keys(&keys);
  for (char *ptr = str_copy; *ptr != '\0' && !(*error); ptr++) {
    if (*ptr >= '0' && *ptr <= '9') {
      guint len_put_str = 0;
      put_str = add_to_string(put_str, ptr, 'n', &len_put_str);
      result = g_slist_prepend(result, g_strdup(put_str));
      ptr += len_put_str - 1;
      reset_keys(&keys);
    } else if (*ptr == 'x') {
      result = g_slist_prepend(result, g_strdup("x"));
      reset_keys(&keys);
    } else if (*ptr == '(') {
      stack = g_slist_prepend(stack, g_strdup("("));
      reset_keys(&keys);
    } else if (*ptr == 'n' || *ptr == 'l' || *ptr == 't' || *ptr == 'a' ||
               *ptr == 'e' || *ptr == 'c' || *ptr == 's') {
      guint len_put_str = 0;
      put_str = add_to_string(put_str, ptr, 'f', &len_put_str);
      stack = g_slist_prepend(stack, g_strdup(put_str));
      ptr += len_put_str - 1;
      reset_keys(&keys);
    } else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/' ||
               *ptr == '%' || *ptr == '^' || *ptr == 'm') {
      ptr += operator_proc(ptr, &result, &stack, &keys);
      reset_keys(&keys);
      keys.is_operator = 1;
    } else if (*ptr == ')') {
      bracket_proc(&result, &stack, error);
      reset_keys(&keys);
    } else if (*ptr == ' ') {
      *error = 0;
    } else {
      *error = 1;
    }
  }
  result = put_to_result(stack, result, error);
  free(put_str);
  free(str_copy);
  g_slist_free_full(stack, free);
  return result;
}

GSList *put_to_result(GSList *tmp, GSList *result, guint *error) {
  while (tmp && !(*error)) {
    if (((char *)tmp->data)[0] == '(') *error = 1;
    result = g_slist_prepend(result, g_strdup((char *)tmp->data));
    tmp = g_slist_next(tmp);
  }
  result = g_slist_reverse(result);
  return result;
}

void bracket_proc(GSList **result, GSList **stack, guint *error) {
  // переносим операторы или функцию из стека в выход(result)
  while (((char *)(*stack)->data)[0] != '(' && *stack) {
    *result = g_slist_prepend(*result, g_strdup((char *)(*stack)->data));
    *stack = pop_from_list(*stack);
  }
  // если стек не пустой, то это ( и мы должны ее удалить
  // иначе ошибка
  if (*stack) {
    *stack = pop_from_list(*stack);
  } else {
    *error = 1;
  }
}

GSList *pop_from_list(GSList *stack) {
  GSList *tmp = stack;
  stack = g_slist_next(stack);
  free(tmp->data);
  g_slist_free_1(tmp);
  return stack;
}

guint operator_proc(char *ptr, GSList **result, GSList **stack,
                    KeysCheck *keys) {
  guint answer = 0;
  char o[2] = {0};
  if (*ptr == '-') {
    if (!(*result)) {
      if (*(ptr + 1) >= '0' && *(ptr + 1) <= '9') *ptr = '~';
    } else {
      if ((*(ptr - 1) == ' ' && *(ptr - 2) == '(') || *(ptr - 1) == '(' ||
          keys->is_operator)
        *ptr = '~';
    }
  }
  if (*ptr == 'm') {
    answer = 2;
    int error_mod = 0;
    char *str_mod = "mod";
    int i = 1;
    while (!error_mod && str_mod[i])
      if (*(++ptr) != str_mod[i++]) error_mod = 1;
    *ptr = '%';
  }
  if (!(*stack)) {
    o[0] = *ptr;
    *stack = g_slist_prepend(*stack, g_strdup(o));
  } else {
    guint stack_pr = operation_priority((char *)(*stack)->data);
    guint ptr_pr = operation_priority(ptr);
    while (stack_pr <= ptr_pr && *stack &&
           !(ptr[0] == '^' && ((char *)(*stack)->data)[0] == '^')) {
      *result = g_slist_prepend(*result, g_strdup((char *)(*stack)->data));
      *stack = pop_from_list(*stack);
      if (*stack) stack_pr = operation_priority((char *)(*stack)->data);
    }
    o[0] = *ptr;
    *stack = g_slist_prepend(*stack, g_strdup(o));
  }
  return answer;
}

guint checking_str_for_err(char *str) {
  guint answer = 0;
  KeysCheck keys;
  reset_keys(&keys);
  int count_bkt = 0;
  for (char *ptr = str; *ptr && !answer; ptr++) {
    if ((*ptr >= '0' && *ptr <= '9') || *ptr == '.' || *ptr == ',' ||
        *ptr == 'x') {
      if (keys.is_bkt_cls) answer = 1;
      reset_keys(&keys);
      keys.is_number = 1;
    }
    if (*ptr == '(') {
      count_bkt++;
      answer = 1;
      if (keys.is_operator || keys.is_function || ptr == str ||
          (ptr > str && *(ptr - 1) == '(')) {
        answer = 0;
        reset_keys(&keys);
      }
    }
    if (*ptr == ')') {
      count_bkt--;
      keys.is_bkt_cls = 1;
    }
    if (*ptr == 'n' || *ptr == 'l' || *ptr == 't' || *ptr == 'a' ||
        *ptr == 'e' || *ptr == 'c' || *ptr == 's') {
      answer = function_check(ptr, str);
      if (!answer) {
        while (*ptr != '(') {
          ptr++;
        }
      }
      ptr--;
      keys.is_function = 1;
    }
    if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/' ||
        *ptr == '%' || *ptr == '^' || *ptr == 'm') {
      answer = 0;
      if (keys.is_operator && *ptr != '-') answer = 1;
      reset_keys(&keys);
      keys.is_operator = 1;
    }
  }
  if (count_bkt != 0) answer = 1;
  if (keys.is_operator) answer = 1;
  return answer;
}

void reset_keys(KeysCheck *keys) {
  keys->is_number = 0;
  keys->is_function = 0;
  keys->is_operator = 0;
  keys->is_bkt_cls = 0;
}

guint operation_priority(char *str) {
  guint answer = 0;
  if (str[0] == '(') answer = 7;
  if (str[0] == '~') answer = 0;
  if (str[0] == '+') answer = 5;
  if (str[0] == '-') answer = 5;
  if (str[0] == '*') answer = 4;
  if (str[0] == '/') answer = 4;
  if (str[0] == '%') answer = 4;
  if (str[0] == 'm') answer = 4;
  if (str[0] == '^') answer = 1;
  return answer;
}

guint function_check(char *ptr, char *str_copy) {
  guint error = 0;
  if (ptr != str_copy)
    if (*(ptr - 1) == ')') error = 1;
  if (!error) {
    error = 1;
    check_word(ptr, "negate(", &error);
    check_word(ptr, "atan(", &error);
    check_word(ptr, "acos(", &error);
    check_word(ptr, "asin(", &error);
    check_word(ptr, "sqrt(", &error);
    check_word(ptr, "tan(", &error);
    check_word(ptr, "log(", &error);
    check_word(ptr, "abs(", &error);
    check_word(ptr, "cos(", &error);
    check_word(ptr, "sin(", &error);
    check_word(ptr, "ln(", &error);
  }
  return error;
}

void check_word(char *ptr, char *str, guint *error) {
  guint i = 0;
  while ((str[i] || ptr[i]) && str[i] == ptr[i]) i++;
  if (str[i] == '\0') *error = 0;
}

char *add_to_string(char *put_str, char *ptr, char lexeme_type,
                    guint *len_put_str) {
  *len_put_str = 0;
  while (is_lexeme_type(*ptr, lexeme_type)) {
    put_str = realloc(put_str, *len_put_str + 1);
    if (*ptr == '.')
      put_str[(*len_put_str)++] = ',';
    else
      put_str[(*len_put_str)++] = *ptr;
    ptr++;
  }
  put_str = realloc(put_str, *len_put_str + 1);
  put_str[*len_put_str] = '\0';
  return put_str;
}

guint is_lexeme_type(char ptr, char lexeme_type) {
  guint answer = 0;
  if (lexeme_type == 'n' &&
      ((ptr >= '0' && ptr <= '9') || ptr == '.' || ptr == ','))
    answer = 1;
  if (lexeme_type == 'f' && ptr != '(') answer = 1;
  return answer;
}