/**
 * @file Parser.c
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
 * @brief       Функция преобразования строки в односвязный список
 *
 * @param str   Входящие данные в виде строки
 * @param A     Выходящие данные в виде односвязного списка
 * @return      0 в случае успеха
 */
int Parser(stack** A, char* str) {
  int res = 0;
  if (Validator(str) == 0) {
    size_t str_len = strlen(str);

    for (size_t i = 0; i < str_len; i++) {
      if ((str[i] > 47 && str[i] < 58) || str[i] == '.') {
        Push(A, 32, atof(str + i), numberCalc, 0);
        i += strspn(str + i, "1234567890.") - 1;
      } else {
        switch (str[i]) {
          case 'x': Push(A, 'x', 0, numberCalc, 0); break;  // внедрить
          case '(': Push(A, '(', 0, bracket_l, 1); break;
          case '*': Push(A, '*', 0, mullCalc, 3); break;
          case '/': Push(A, '/', 0, delCalc, 3); break;
          case '^': Push(A, '^', 0, scalCalc, 4); break;
          case 'm': Push(A, 'm', 0, modCalc, 4); break;
          case 's': Push(A, 's', 0, sinCalc, 5); break;
          case 'c': Push(A, 'c', 0, cosCalc, 5); break;
          case 't': Push(A, 't', 0, tanCalc, 5); break;
          case 'C': Push(A, 'C', 0, acosCalc, 5); break;
          case 'S': Push(A, 'S', 0, asinCalc, 5); break;
          case 'T': Push(A, 'T', 0, atanCalc, 5); break;
          case 'q': Push(A, 'q', 0, sqrtCalc, 5); break;
          case 'l': Push(A, 'l', 0, lnCalc, 5); break;
          case 'L': Push(A, 'L', 0, logCalc, 5); break;
          case ')': Push(A, ')', 0, bracket_r, 6); break;
          case '+':
            if ((str[i] == '+' && str[i - 1] == '(') || (str[0] == ' ' && str[1] == '+') || (str[0] == '+')) {
              Push(A, 32, 0, numberCalc, 0);
              Push(A, '+', 0, plusCalc, 2);
            } else
              Push(A, '+', 0, plusCalc, 2);
            break;
          case '-':
            if ((str[i] == '-' && str[i - 1] == '(') || (str[0] == ' ' && str[1] == '-') || (str[0] == '-')) {
              Push(A, 32, 0, numberCalc, 0);
              Push(A, '-', 0, minusCalc, 2);
            } else
              Push(A, '-', 0, minusCalc, 2);
            break;
          default: break;
        }
      }
    }
  } else
    res = 1;
  return res;
}
