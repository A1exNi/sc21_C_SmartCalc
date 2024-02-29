#include "s21_polish_notation.h"
#include "test_main.h"

START_TEST(notation_1) {
  char *str_test = "224 + sin(1 + 2 * 3)";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  str_orig = g_slist_prepend(str_orig, g_strdup("224"));
  str_orig = g_slist_prepend(str_orig, g_strdup("1"));
  str_orig = g_slist_prepend(str_orig, g_strdup("2"));
  str_orig = g_slist_prepend(str_orig, g_strdup("3"));
  str_orig = g_slist_prepend(str_orig, g_strdup("*"));
  str_orig = g_slist_prepend(str_orig, g_strdup("+"));
  str_orig = g_slist_prepend(str_orig, g_strdup("sin"));
  str_orig = g_slist_prepend(str_orig, g_strdup("+"));
  str_orig = g_slist_reverse(str_orig);
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  GSList *tmp_a = str_answer;
  GSList *tmp_o = str_orig;
  while (tmp_o) {
    ck_assert_str_eq((char *)tmp_a->data, (char *)tmp_o->data);
    tmp_a = g_slist_next(tmp_a);
    tmp_o = g_slist_next(tmp_o);
  }
  ck_assert_int_eq(error, 0);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_2) {
  char *str_test = "22.4 + 34,1";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  str_orig = g_slist_prepend(str_orig, g_strdup("22,4"));
  str_orig = g_slist_prepend(str_orig, g_strdup("34,1"));
  str_orig = g_slist_prepend(str_orig, g_strdup("+"));
  str_orig = g_slist_reverse(str_orig);
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  GSList *tmp_a = str_answer;
  GSList *tmp_o = str_orig;
  while (tmp_o) {
    ck_assert_str_eq((char *)tmp_a->data, (char *)tmp_o->data);
    tmp_a = g_slist_next(tmp_a);
    tmp_o = g_slist_next(tmp_o);
  }
  ck_assert_int_eq(error, 0);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_3) {
  char *str_test = "+2";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  str_orig = g_slist_prepend(str_orig, g_strdup("2"));
  str_orig = g_slist_prepend(str_orig, g_strdup("+"));
  str_orig = g_slist_reverse(str_orig);
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  GSList *tmp_a = str_answer;
  GSList *tmp_o = str_orig;
  while (tmp_o) {
    ck_assert_str_eq((char *)tmp_a->data, (char *)tmp_o->data);
    tmp_a = g_slist_next(tmp_a);
    tmp_o = g_slist_next(tmp_o);
  }
  ck_assert_int_eq(error, 0);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_4) {
  char *str_test = "-2";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  str_orig = g_slist_prepend(str_orig, g_strdup("2"));
  str_orig = g_slist_prepend(str_orig, g_strdup("~"));
  str_orig = g_slist_reverse(str_orig);
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  GSList *tmp_a = str_answer;
  GSList *tmp_o = str_orig;
  while (tmp_o) {
    ck_assert_str_eq((char *)tmp_a->data, (char *)tmp_o->data);
    tmp_a = g_slist_next(tmp_a);
    tmp_o = g_slist_next(tmp_o);
  }
  ck_assert_int_eq(error, 0);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_5) {
  char *str_test = "1 + sin(-2)";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  str_orig = g_slist_prepend(str_orig, g_strdup("1"));
  str_orig = g_slist_prepend(str_orig, g_strdup("2"));
  str_orig = g_slist_prepend(str_orig, g_strdup("~"));
  str_orig = g_slist_prepend(str_orig, g_strdup("sin"));
  str_orig = g_slist_prepend(str_orig, g_strdup("+"));
  str_orig = g_slist_reverse(str_orig);
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  GSList *tmp_a = str_answer;
  GSList *tmp_o = str_orig;
  while (tmp_o) {
    ck_assert_str_eq((char *)tmp_a->data, (char *)tmp_o->data);
    tmp_a = g_slist_next(tmp_a);
    tmp_o = g_slist_next(tmp_o);
  }
  ck_assert_int_eq(error, 0);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_6) {
  char *str_test = "1 + 2 * 3 * 4";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  str_orig = g_slist_prepend(str_orig, g_strdup("1"));
  str_orig = g_slist_prepend(str_orig, g_strdup("2"));
  str_orig = g_slist_prepend(str_orig, g_strdup("3"));
  str_orig = g_slist_prepend(str_orig, g_strdup("*"));
  str_orig = g_slist_prepend(str_orig, g_strdup("4"));
  str_orig = g_slist_prepend(str_orig, g_strdup("*"));
  str_orig = g_slist_prepend(str_orig, g_strdup("+"));
  str_orig = g_slist_reverse(str_orig);
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  GSList *tmp_a = str_answer;
  GSList *tmp_o = str_orig;
  while (tmp_o) {
    ck_assert_str_eq((char *)tmp_a->data, (char *)tmp_o->data);
    tmp_a = g_slist_next(tmp_a);
    tmp_o = g_slist_next(tmp_o);
  }
  ck_assert_int_eq(error, 0);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_7) {
  char *str_test =
      "negate(2) + atan(-1/2) - acos(+4) * asin(2) / \
                    (tan(1) + log(10) * (abs(-5) - cos(1/2))) % sin(1) mod ln(10) ^ sqrt(9)";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  str_orig = g_slist_prepend(str_orig, g_strdup("2"));
  str_orig = g_slist_prepend(str_orig, g_strdup("negate"));
  str_orig = g_slist_prepend(str_orig, g_strdup("1"));
  str_orig = g_slist_prepend(str_orig, g_strdup("~"));
  str_orig = g_slist_prepend(str_orig, g_strdup("2"));
  str_orig = g_slist_prepend(str_orig, g_strdup("/"));
  str_orig = g_slist_prepend(str_orig, g_strdup("atan"));
  str_orig = g_slist_prepend(str_orig, g_strdup("+"));
  str_orig = g_slist_prepend(str_orig, g_strdup("4"));
  str_orig = g_slist_prepend(str_orig, g_strdup("+"));
  str_orig = g_slist_prepend(str_orig, g_strdup("acos"));
  str_orig = g_slist_prepend(str_orig, g_strdup("2"));
  str_orig = g_slist_prepend(str_orig, g_strdup("asin"));
  str_orig = g_slist_prepend(str_orig, g_strdup("*"));
  str_orig = g_slist_prepend(str_orig, g_strdup("1"));
  str_orig = g_slist_prepend(str_orig, g_strdup("tan"));
  str_orig = g_slist_prepend(str_orig, g_strdup("10"));
  str_orig = g_slist_prepend(str_orig, g_strdup("log"));
  str_orig = g_slist_prepend(str_orig, g_strdup("5"));
  str_orig = g_slist_prepend(str_orig, g_strdup("~"));
  str_orig = g_slist_prepend(str_orig, g_strdup("abs"));
  str_orig = g_slist_prepend(str_orig, g_strdup("1"));
  str_orig = g_slist_prepend(str_orig, g_strdup("2"));
  str_orig = g_slist_prepend(str_orig, g_strdup("/"));
  str_orig = g_slist_prepend(str_orig, g_strdup("cos"));
  str_orig = g_slist_prepend(str_orig, g_strdup("-"));
  str_orig = g_slist_prepend(str_orig, g_strdup("*"));
  str_orig = g_slist_prepend(str_orig, g_strdup("+"));
  str_orig = g_slist_prepend(str_orig, g_strdup("/"));
  str_orig = g_slist_prepend(str_orig, g_strdup("1"));
  str_orig = g_slist_prepend(str_orig, g_strdup("sin"));
  str_orig = g_slist_prepend(str_orig, g_strdup("%"));
  str_orig = g_slist_prepend(str_orig, g_strdup("10"));
  str_orig = g_slist_prepend(str_orig, g_strdup("ln"));
  str_orig = g_slist_prepend(str_orig, g_strdup("9"));
  str_orig = g_slist_prepend(str_orig, g_strdup("sqrt"));
  str_orig = g_slist_prepend(str_orig, g_strdup("^"));
  str_orig = g_slist_prepend(str_orig, g_strdup("%"));
  str_orig = g_slist_prepend(str_orig, g_strdup("-"));
  str_orig = g_slist_reverse(str_orig);
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  GSList *tmp_a = str_answer;
  GSList *tmp_o = str_orig;
  while (tmp_o && !error) {
    ck_assert_str_eq((char *)tmp_a->data, (char *)tmp_o->data);
    tmp_a = g_slist_next(tmp_a);
    tmp_o = g_slist_next(tmp_o);
  }
  ck_assert_int_eq(error, 0);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

Suite *notation_suite(void) {
  Suite *s = suite_create("Notation");
  TCase *tc_notation = tcase_create("Notation");
  tcase_add_test(tc_notation, notation_1);
  tcase_add_test(tc_notation, notation_2);
  tcase_add_test(tc_notation, notation_3);
  tcase_add_test(tc_notation, notation_4);
  tcase_add_test(tc_notation, notation_5);
  tcase_add_test(tc_notation, notation_6);
  tcase_add_test(tc_notation, notation_7);
  suite_add_tcase(s, tc_notation);
  return s;
}