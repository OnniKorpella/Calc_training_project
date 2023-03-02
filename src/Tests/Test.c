#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 256
#include "../Calc.h"
stack *A    = NULL;
stack *B    = NULL;
stack *Exit = NULL;

void FreeM() {
  FreeStack(A);
  FreeStack(B);
  FreeStack(Exit);
  free(A);
  free(B);
  free(Exit);
}

START_TEST(notation_1) {
  char str[] = "2+2";
  Parser(&A, str);
  Reverse(&A, &B);
  int res = Notation(&B, &A, &Exit);
  ck_assert_int_eq(res, 0);
  FreeM;
}
END_TEST

START_TEST(validator_1) {
  char input[SIZE] = "3 +";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 101);
}
END_TEST

START_TEST(validator_2) {
  char input[SIZE] = "-(8.0009)+(-2.0) -1 - 2";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 0);
}
END_TEST

START_TEST(validator_3) {
  char input[SIZE] = "%3-4sin(1)";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 113);
}
END_TEST

START_TEST(validator_4) {
  char input[SIZE] = " -(-8 * z(-2))) -1 - 2";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 120);
}
END_TEST

START_TEST(validator_5) {
  char input[SIZE] = " (8.0 + (-2)) -1 - 2(";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 120);
}
END_TEST

START_TEST(validator_6) {
  char input[SIZE] = " (8.0 + (-2)) -1 -- 2";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 107);
}
END_TEST

START_TEST(validator_7) {
  char input[SIZE] = "(8+(-2))-1%2";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 0);
}
END_TEST

START_TEST(validator_8) {
  char input[SIZE] = "1 % 2 + cos() + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) +l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_9) {
  char input[SIZE] = "1%2+cos(8.0)+sin(-2)+tan(acos(x)+asin(x))+atan(0)+sqrt(1)+l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_10) {
  char input[SIZE] = "1 % 2 + cos8.0) + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) +l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 120);
}
END_TEST

START_TEST(validator_11) {
  char input[SIZE] = "1 % 2 + cos(8.0) + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) +l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_12) {
  char input[SIZE] = "1 % 2 + cos(x8.0) + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) +l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_13) {
  char input[SIZE] = "1 % 2 + x(8.0) + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) +l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_14) {
  char input[SIZE] = "1 % 2 + x8 + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) +l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_15) {
  char input[SIZE] = "1 % 2 + x8 + xsin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) +l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_16) {
  char input[SIZE] = "sin(-2)*tan(acos(x)/asin(x))^atan(0)+sqrt(-1)+l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_17) {
  char input[SIZE] = "l_n(-2)*tan(acos(x)/asin(x))^atan(0)+sqrt(-1)+l_n(log(2))";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_18) {
  char input[SIZE] = "x + 1";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(validator_19) {
  char input[SIZE] = "xx";
  int  v           = Validator(input);
  ck_assert_int_eq(v, 115);
}
END_TEST

START_TEST(calc_1) {
  char   str[] = "3+3";
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);

  ck_assert_int_eq(6, Calc(&Exit));

  FreeM;
}
END_TEST

START_TEST(calc_2) {
  char   str[] = "6-1";
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), 5, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_3) {
  char   str[]  = "cos(10)";
  double etalon = -0.83907152907;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}

END_TEST
START_TEST(calc_4) {
  char   str[]  = "cos(11)+66-90/70";
  double etalon = 64.7187114123;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST
START_TEST(calc_5) {
  char   str[]  = "-10+(cos(101))/102";
  double etalon = -9.99125485422;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST
START_TEST(calc_6) {
  char   str[]  = "-10+(cos(101))";
  double etalon = -9.10799513021;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_7) {
  char   str[]  = "10+(cos(101))";
  double etalon = 10.8920048698;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_8) {
  char   str[]  = "2^2^2";
  double etalon = 16;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);

  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_9) {
  char   str[]  = "2^2^2^2";
  double etalon = 65536;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_10) {
  char   str[]  = "tan(log(3)) + 3 / 8";
  double etalon = 0.89195732177;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_11) {
  char   str[]  = "tan(log(3)) + 3 / 8+10/8^5";
  double etalon = 0.89226249755;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);

  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);

  FreeM;
}

START_TEST(calc_12) {
  char   str[]  = "ln(100)";
  double etalon = 4.60517018599;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_14) {
  char   str[]  = "log(100)";
  double etalon = 2;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_15) {
  char   str[]  = "2^2^2";
  double etalon = 16;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_16) {
  char   str[]  = "2^2^2^2";
  double etalon = 65536;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_161) {
  char   str[]  = "0.1^2^2^2^2";
  double etalon = 0;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_17) {
  char   str[]  = "-2";
  double etalon = -2;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_18) {
  char   str[]  = "(-2)";
  double etalon = -2;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_19) {
  char   str[]  = "10+(-2)";
  double etalon = 8;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_20) {
  char   str[]  = "10+(-(-2))";
  double etalon = 12;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_21) {
  char   str[]  = "10+(-(-(-2)))";
  double etalon = 8;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_22) {
  char   str[]  = "sin(cos(111))";
  double etalon = -0.48165683451;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST

START_TEST(calc_23) {
  char   str[]  = "tan(sqrt(222))";
  double etalon = -1.04688321107;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST
START_TEST(calc_24) {
  char   str[]  = "sin(cos(111))+tan(sqrt(222))";
  double etalon = -1.52854004559;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);

  FreeM;
}
END_TEST
START_TEST(calc_25) {
  char   str[]  = "78 mod 33";
  double etalon = 12;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);

  FreeM;
}
END_TEST

START_TEST(calc_26) {
  char   str[]  = "2/1+2+3+4*5*6^7-12+((1000+500*2)*201)+sin(1)";
  double etalon = 6000715.841471;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);

  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  ;
  FreeM;
}
END_TEST

START_TEST(calc_27) {
  char   str[]  = "2/1+2+3+4*5*6^7-12+((1000+500*2)*201)";
  double etalon = 6000715;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq(etalon, Calc(&Exit));
  FreeM;
}
END_TEST
START_TEST(calc_28) {
  char   str[]  = "3+4*2/(1-5)^2^3";
  double etalon = 3.00012207031;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-07);
  FreeM;
}
END_TEST
START_TEST(calc_29) {
  char   str[]  = "2/1+2+3+4*5*6^7-727mod728+((1000+500*2)*201)+sin(1)";
  double etalon = 6000000.84147;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-06);
  FreeM;
}
END_TEST

START_TEST(calc_30) {
  char   str[]  = "sin(cos(1))+tan(sqrt(2))-((3))*(4)";
  double etalon = -5.15148557443;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-06);

  FreeM;
}
END_TEST

START_TEST(calc_31) {
  char   str[]  = "1+2+3+4*5*6^7-727mod728+((1000+500*2)*201)+sin(1)";
  double etalon = 5999999.84147;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-06);
  FreeM;
}
END_TEST
START_TEST(calc_32) {
  char   str[]  = "cos(32.2^4.1)*sqrt(3.3)";
  double etalon = 0.708380;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-06);
  FreeM;
}
END_TEST

START_TEST(calc_33) {
  char   str[]  = "ln(12.5)";
  double etalon = 2.52573;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-05);
  FreeM;
}
END_TEST

START_TEST(calc_34) {
  char   str[]  = "log(12.5)";
  double etalon = 1.09691001301;
  stack *A = NULL, *B = NULL, *Exit = NULL;
  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);
  Notation(&B, &A, &Exit);
  ck_assert_double_eq_tol(Calc(&Exit), etalon, 1e-05);
  FreeM;
}
END_TEST

START_TEST(debit_1) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(0, 10000, 12, 10, 100, 6, 0, 0, res_sum, dohod, nalog);

  ck_assert_double_eq(*res_sum, 11105);
  ck_assert_double_eq(*dohod, 1005);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_2) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(0, 100000, 60, 10, 100, 6, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq(*res_sum, 151125);
  ck_assert_double_eq(*dohod, 50225);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_3) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(0, 100000000, 12, 10, 0, 0, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*res_sum, 1.1e+08, 1e-07);
  ck_assert_double_eq_tol(*dohod, 1e+07, 1e-07);
  ck_assert_double_eq_tol(*nalog, 1.29025e+06, 1e-07);
  free(res_sum);
  free(dohod);
  free(nalog);
}
END_TEST
START_TEST(debit_4) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(1, 10000, 12, 10, 0, 0, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*res_sum, 11047.1, 1e-01);
  ck_assert_double_eq_tol(*dohod, 1047.13, 1e-03);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_5) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(1, 10000, 12, 10, 80, 1, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*res_sum, 11972.4, 1e-01);
  ck_assert_double_eq_tol(*dohod, 1092.38, 1e-01);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_6) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(1, 10000, 12, 10, 0, 0, 100, 3, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*res_sum, 10731.7, 1e-01);
  ck_assert_double_eq_tol(*dohod, 1031.75, 1e-01);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_7) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(0, 10000, 12, 10, 0, 0, 100, 3, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*res_sum, 10685, 1e-01);
  ck_assert_double_eq_tol(*dohod, 985, 1e-01);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_8) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(0, 100000, 60, 10, 0, 0, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*res_sum, 150000, 1e-05);
  ck_assert_double_eq_tol(*dohod, 50000, 1e-05);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_9) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(0, 10000000, 60, 10, 0, 0, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*res_sum, 15000000, 1e-05);
  ck_assert_double_eq_tol(*dohod, 5e+06, 1e-05);
  ck_assert_double_eq(*nalog, 640250);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_10) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(0, 100000, 60, 5, 0, 0, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*dohod, 25000, 1e-05);
  ck_assert_double_eq_tol(*res_sum, 125000, 1e-05);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_11) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(0, 100000, 60, 5, 0, 0, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*dohod, 25000, 1e-05);
  ck_assert_double_eq_tol(*res_sum, 125000, 1e-05);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_12) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(0, 100000, 60, 5.5, 0, 0, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*dohod, 27500, 1e-05);
  ck_assert_double_eq_tol(*res_sum, 127500, 1e-05);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_14) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(1, 100000, 60, 10, 0, 0, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*dohod, 64530.893487, 1e-01);
  ck_assert_double_eq_tol(*res_sum, 164530.893487, 1e-01);
  ck_assert_double_eq(*nalog, 0);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_15) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(1, 100000, 60, 10, 800, 1, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*dohod, 78480.551227, 1e-05);
  ck_assert_double_eq_tol(*res_sum, 225680.551227, 1e-05);
  ck_assert_double_eq_tol(*nalog, 452.472, 1e-01);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST
START_TEST(debit_16) {
  double *res_sum = calloc(1, sizeof(double));
  double *dohod   = calloc(1, sizeof(double));
  double *nalog   = calloc(1, sizeof(double));
  CalcDebit(1, 100000, 60, 10, 800, 1, 0, 0, res_sum, dohod, nalog);
  ck_assert_double_eq_tol(*dohod, 78480.551227, 1e-05);
  ck_assert_double_eq_tol(*res_sum, 225680.551227, 1e-05);
  ck_assert_double_eq_tol(*nalog, 452.472, 1e-01);
  free(res_sum), free(dohod), free(nalog);
}
END_TEST

START_TEST(credit_1) {
  double *monthlyPaymentFirst = calloc(1, sizeof(double));
  double *monthlyPaymentLast  = calloc(1, sizeof(double));
  double *overPayment         = calloc(1, sizeof(double));
  double *finalSum            = calloc(1, sizeof(double));

  CreditCalc(100000, 12, 10, 0, monthlyPaymentFirst, monthlyPaymentLast, overPayment, finalSum);
  ck_assert_double_eq_tol(*monthlyPaymentFirst, 0, 1e-05);
  ck_assert_double_eq_tol(*monthlyPaymentLast, 8791.59, 1e-02);
  ck_assert_double_eq_tol(*overPayment, 5499.06, 1e-02);
  ck_assert_double_eq_tol(*finalSum, 105499.06, 1e-02);
  free(monthlyPaymentFirst), free(monthlyPaymentLast), free(overPayment), free(finalSum);
}
END_TEST
START_TEST(credit_2) {
  double *monthlyPaymentFirst = calloc(1, sizeof(double));
  double *monthlyPaymentLast  = calloc(1, sizeof(double));
  double *overPayment         = calloc(1, sizeof(double));
  double *finalSum            = calloc(1, sizeof(double));

  CreditCalc(100000, 12, 10, 1, monthlyPaymentFirst, monthlyPaymentLast, overPayment, finalSum);
  ck_assert_double_eq_tol(*monthlyPaymentFirst, 9166.67, 1e-02);
  ck_assert_double_eq_tol(*monthlyPaymentLast, 8333.33, 1e-02);
  ck_assert_double_eq_tol(*overPayment, 5416.67, 1e-02);
  ck_assert_double_eq_tol(*finalSum, 105417.01, 1e-00);
  free(monthlyPaymentFirst), free(monthlyPaymentLast), free(overPayment), free(finalSum);
}
END_TEST

int main(void) {
  Suite   *s1 = suite_create("Core");
  TCase   *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int      nf;
  suite_add_tcase(s1, tc);

  tcase_add_test(tc, credit_1);
  tcase_add_test(tc, credit_2);
  tcase_add_test(tc, debit_1);
  tcase_add_test(tc, debit_2);
  tcase_add_test(tc, debit_3);
  tcase_add_test(tc, debit_4);
  tcase_add_test(tc, debit_5);
  tcase_add_test(tc, debit_6);
  tcase_add_test(tc, debit_7);
  tcase_add_test(tc, debit_8);
  tcase_add_test(tc, debit_9);
  tcase_add_test(tc, debit_10);
  tcase_add_test(tc, debit_11);
  tcase_add_test(tc, debit_12);
  tcase_add_test(tc, debit_14);
  tcase_add_test(tc, debit_15);
  tcase_add_test(tc, calc_1);
  tcase_add_test(tc, calc_2);
  tcase_add_test(tc, calc_3);
  tcase_add_test(tc, calc_4);
  tcase_add_test(tc, calc_5);
  tcase_add_test(tc, calc_6);
  tcase_add_test(tc, calc_7);
  tcase_add_test(tc, calc_8);
  tcase_add_test(tc, calc_9);
  tcase_add_test(tc, calc_10);
  tcase_add_test(tc, calc_11);
  tcase_add_test(tc, calc_12);
  tcase_add_test(tc, calc_14);
  tcase_add_test(tc, calc_15);
  tcase_add_test(tc, calc_16);
  tcase_add_test(tc, calc_161);
  tcase_add_test(tc, calc_17);
  tcase_add_test(tc, calc_18);
  tcase_add_test(tc, calc_19);
  tcase_add_test(tc, calc_20);
  tcase_add_test(tc, calc_21);
  tcase_add_test(tc, calc_22);
  tcase_add_test(tc, calc_23);
  tcase_add_test(tc, calc_24);
  tcase_add_test(tc, calc_25);
  tcase_add_test(tc, calc_26);
  tcase_add_test(tc, calc_27);
  tcase_add_test(tc, calc_28);
  tcase_add_test(tc, calc_29);
  tcase_add_test(tc, calc_30);
  tcase_add_test(tc, calc_31);
  tcase_add_test(tc, calc_32);
  tcase_add_test(tc, calc_33);
  tcase_add_test(tc, calc_34);
  tcase_add_test(tc, notation_1);
  tcase_add_test(tc, validator_1);
  tcase_add_test(tc, validator_2);
  tcase_add_test(tc, validator_3);
  tcase_add_test(tc, validator_4);
  tcase_add_test(tc, validator_5);
  tcase_add_test(tc, validator_6);
  tcase_add_test(tc, validator_7);
  tcase_add_test(tc, validator_8);
  tcase_add_test(tc, validator_9);
  tcase_add_test(tc, validator_10);
  tcase_add_test(tc, validator_11);
  tcase_add_test(tc, validator_12);
  tcase_add_test(tc, validator_13);
  tcase_add_test(tc, validator_14);
  tcase_add_test(tc, validator_15);
  tcase_add_test(tc, validator_16);
  tcase_add_test(tc, validator_17);
  tcase_add_test(tc, validator_18);
  tcase_add_test(tc, validator_19);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
