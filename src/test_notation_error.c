#include "s21_polish_notation.h"
#include "test_main.h"

START_TEST(notation_error_1) {
  char *str_test = "224 + sinu(1 + 2 * 3)";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_2) {
  char *str_test = "22.4 + \0 34,1";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_3) {
  char *str_test = "+2\n";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_4) {
  char *str_test = "-2 *";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_5) {
  char *str_test = "1 + sincos(-2)";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_6) {
  char *str_test = "sin(1)cos(1)";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_7) {
  char *str_test = "1 + (2+3)2";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_8) {
  char *str_test = "1(2+3) + 2";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_9) {
  char *str_test = "1 * (2 + 3))";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_10) {
  char *str_test = "1 * ((2 + 3)";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

START_TEST(notation_error_11) {
  char *str_test = "neg";
  GSList *str_answer = NULL;
  GSList *str_orig = NULL;
  guint error = 0;
  str_answer = polish_notation(str_test, str_answer, &error);
  ck_assert_int_eq(error, 1);
  g_slist_free_full(str_answer, free);
  g_slist_free_full(str_orig, free);
}
END_TEST

Suite *notation_error_suite(void) {
  Suite *s = suite_create("Notation Error");
  TCase *tc_notation = tcase_create("Notation Error");
  tcase_add_test(tc_notation, notation_error_1);
  tcase_add_test(tc_notation, notation_error_2);
  tcase_add_test(tc_notation, notation_error_3);
  tcase_add_test(tc_notation, notation_error_4);
  tcase_add_test(tc_notation, notation_error_5);
  tcase_add_test(tc_notation, notation_error_6);
  tcase_add_test(tc_notation, notation_error_7);
  tcase_add_test(tc_notation, notation_error_8);
  tcase_add_test(tc_notation, notation_error_9);
  tcase_add_test(tc_notation, notation_error_10);
  tcase_add_test(tc_notation, notation_error_11);
  suite_add_tcase(s, tc_notation);
  return s;
}