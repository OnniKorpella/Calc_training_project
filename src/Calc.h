/**
 * @file Calc.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SMART_CALC_H_
#define SMART_CALC_H_
// #include <stdio.h>
// #include <string.h>
// #include <math.h>

#include "../data-samples/color.h"
/**
 * @brief Сруктура для записи лексемы
 * 
 * @param str       char показывает знак операции
 * @param number    число 
 * @param priority  приоритет лексемы
 * @param type      тип лексемы
 * @param next      указатель на следующюю структуру 
 */
typedef struct Stack {
  char          str;
  double        number;
  int           priority;
  int           type;
  struct Stack *next;
} stack;

typedef enum {      // type   //priority
  numberCalc = 1,   // 0
  xCalc      = 2,   // 0
  plusCalc   = 3,   // +      // 2
  minusCalc  = 4,   // -      // 2
  mullCalc   = 5,   // *      // 3
  delCalc    = 6,   // /      // 3
  scalCalc   = 7,   // ^      // 4
  modCalc    = 8,   // % m    // 4
  sinCalc    = 9,   // s---|  // 5
  cosCalc    = 10,  // c   |  // 5
  tanCalc    = 11,  // t   |  // 5
  acosCalc   = 12,  // C   |  // 5
  asinCalc   = 13,  // S   |  // 5
  atanCalc   = 14,  // T   |  // 5
  sqrtCalc   = 15,  // q √ |  // 5
  lnCalc     = 16,  // l   |  // 5
  logCalc    = 17,  // L---|  // 5
  bracket_l  = 18,  // (      // 1
  bracket_r  = 19,  // )      // 6
  un_minus   = 20,  // u -    // 2
} type_t;

// size_t GetSize(const stack *head);
void   Push(stack **A, char str, double number, int type, int priority);
int    Pop(stack **head);
// char   Peek(const stack *head);
void   FreeStack(stack *A);
void   PrintStack(const stack *A);
// char   SearchForSigns(char A);
// char   SearchForNumbers(char A);
int    Validator(char *str);
int    Parser(stack **A, char *str);
void   Reverse(stack **A, stack **B_Revers);
int    Notation(stack **B_Revers, stack **A, stack **Exit);
double Calc(stack **Exit);
double apply_function(int function_type, double *value_1);
double apply_operator(int operator_type, double *value_1, double *value_2);
void   display(char *str);
double display_double(char *str);
void   CalcDebit(int capital, double sum, double srok, double stavka, double plus, double plusMonth, double minus, double minusMonth, double *sumFin, double *percent, double *taxFin);
void   CreditCalc(double sum, double period, double rate, int payType, double *monthlyPaymentFirst, double *monthlyPaymentLast, double *overPayment, double *finalSum);

#endif  //  SMART_CALC_H_
