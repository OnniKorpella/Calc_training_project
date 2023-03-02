
/**
 * @file Display.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Calc.h"
/**
 * @brief     Главная функция, в которой определена вся логика калькулятора. Вызывается во фронте
 *
 * @param str Строка с выражением для подсчета 
 */
void display(char* str) {
  stack* A    = NULL;
  stack* B    = NULL;
  stack* Exit = NULL;

  Validator(str);
  Parser(&A, str);
  Reverse(&A, &B);         // переворачиваем стек А - результат в B
  Notation(&B, &A, &Exit); /*  подаем B_Revers A-временный стек */
  double res = Calc(&Exit);
  FreeStack(A);
  FreeStack(B);
  FreeStack(Exit);
  char buff[256];
  sprintf(buff, "%f", res);
  strcpy(str, buff);
}
/**
 * @brief     Главная функция, в которой определена вся логика калькулятора. Вызывается во фронте
 * , необходима для выдачи результата в double. Необходима для граффика
 *
 * @param str Строка с выражением для подсчета 
 */
double display_double(char* str) {
  stack* A    = NULL;
  stack* B    = NULL;
  stack* Exit = NULL;

  Parser(&A, str);
  Reverse(&A, &B);         // переворачиваем стек А -результат в B
  Notation(&B, &A, &Exit); /*  подаем B_Revers A-временный стек */
  double res = Calc(&Exit);
  FreeStack(A);
  FreeStack(B);
  FreeStack(Exit);
  return res;
}
