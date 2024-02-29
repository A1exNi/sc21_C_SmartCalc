#include "s21_polish_notation.h"
#include "test_main.h"

START_TEST(polish_add) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("2.3"));
  polish_list = g_slist_prepend(polish_list, g_strdup("+"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, 224 + 2.3);
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_sub) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("2.3"));
  polish_list = g_slist_prepend(polish_list, g_strdup("-"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, 224 - 2.3);
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_mult) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("2.3"));
  polish_list = g_slist_prepend(polish_list, g_strdup("*"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, 224 * 2.3);
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_div) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("2.3"));
  polish_list = g_slist_prepend(polish_list, g_strdup("/"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, 224 / 2.3);
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_fmod) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("2.3"));
  polish_list = g_slist_prepend(polish_list, g_strdup("%"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, fmod(224, 2.3));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_pow) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("2.3"));
  polish_list = g_slist_prepend(polish_list, g_strdup("^"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, pow(224, 2.3));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_cos) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("cos"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, cos(224));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_sin) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("sin"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, sin(224));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_tan) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("tan"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_float_eq(answer, tan(224));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_acos) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("0.5"));
  polish_list = g_slist_prepend(polish_list, g_strdup("acos"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_float_eq(answer, acos(0.5));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_asin) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("0.5"));
  polish_list = g_slist_prepend(polish_list, g_strdup("asin"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_float_eq(answer, asin(0.5));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_atan) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("atan"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, atan(224));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_sqrt) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("sqrt"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, sqrt(224));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_ln) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("ln"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, log(224));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_log) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("log"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, log10(224));
  g_slist_free_full(polish_list, free);
}
END_TEST

START_TEST(polish_negate) {
  GSList *polish_list = NULL;
  polish_list = g_slist_prepend(polish_list, g_strdup("224"));
  polish_list = g_slist_prepend(polish_list, g_strdup("negate"));
  polish_list = g_slist_reverse(polish_list);
  double answer = polish_calc(polish_list, NULL);
  ck_assert_double_eq(answer, 224 * (-1.0));
  g_slist_free_full(polish_list, free);
}
END_TEST

Suite *notation_calc_suite(void) {
  Suite *s = suite_create("Notation Calc");
  TCase *tc_notation = tcase_create("Notation Calc");
  tcase_add_test(tc_notation, polish_add);
  tcase_add_test(tc_notation, polish_sub);
  tcase_add_test(tc_notation, polish_mult);
  tcase_add_test(tc_notation, polish_div);
  tcase_add_test(tc_notation, polish_fmod);
  tcase_add_test(tc_notation, polish_pow);
  tcase_add_test(tc_notation, polish_cos);
  tcase_add_test(tc_notation, polish_sin);
  tcase_add_test(tc_notation, polish_tan);
  tcase_add_test(tc_notation, polish_acos);
  tcase_add_test(tc_notation, polish_asin);
  tcase_add_test(tc_notation, polish_atan);
  tcase_add_test(tc_notation, polish_sqrt);
  tcase_add_test(tc_notation, polish_ln);
  tcase_add_test(tc_notation, polish_log);
  tcase_add_test(tc_notation, polish_negate);
  suite_add_tcase(s, tc_notation);
  return s;
}