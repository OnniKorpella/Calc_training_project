/**
 * @file Calc.c
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
 * @brief         Функция подсчета 
 *
 * @param Exit    Входящий список в постфиксной записи
 * @return        Возвращает результат вычислений в double
 */
double Calc(stack** Exit) {
  stack* temp = NULL;
  stack* sort = NULL;
  Reverse(Exit, &temp);
  double Total_Result = 0.0;
  int    i            = 0;
  while (temp != NULL) {
    if (temp != NULL && temp->type == numberCalc) {
      Push(&sort, 32, temp->number, temp->type, temp->priority);
      Pop(&temp);
      i++;
    } else if (temp != NULL && (temp->type >= plusCalc && temp->type <= modCalc)) {
      double sort_Popped_value = sort->number;
      Pop(&sort);
      Total_Result = apply_operator(temp->type, &sort->number, &sort_Popped_value);
      Pop(&sort);
      Push(&sort, 32, Total_Result, 0, 0);
      Pop(&temp);
      if (temp == NULL) {
        break;
      }
      i++;
    } else if (temp != NULL && temp->type >= 9 && temp->type <= 17) {
      double sort_Popped_value = sort->number;
      Pop(&sort);
      Total_Result = apply_function(temp->type, &sort_Popped_value);
      Push(&sort, 32, Total_Result, 0, 0);
      Pop(&temp);
      if (temp == NULL) {
        break;
      }
      i++;
    }
  }

  return Total_Result;
}
/**
 * @brief                  Подфункция подсчета 
 *
 * @param function_type    Тип операции
 * @param value_1          Число для операции
 * @return                 Возвращает результат вычислений в double
 */
double apply_function(int function_type, double* value_1) {
  double result = 0.0;
  if (function_type == cosCalc)
    result = cos(*value_1);

  else if (function_type == sinCalc)
    result = sin(*value_1);

  else if (function_type == tanCalc)
    result = tan(*value_1);

  else if (function_type == acosCalc)
    result = acos(*value_1);

  else if (function_type == asinCalc)
    result = asin(*value_1);

  else if (function_type == atanCalc)
    result = atan(*value_1);

  else if (function_type == sqrtCalc)
    result = sqrt(*value_1);

  else if (function_type == lnCalc)
    result = log(*value_1);

  else if (function_type == logCalc)
    result = log10(*value_1);

  return result;
}
/**
 * @brief                  Подфункция подсчета 
 *
 * @param function_type    Тип операции
 * @param value_1          Число для операции 1 
 * @param value_2          Число для операции 2 
 * @return                 Возвращает результат вычислений в double
 */
double apply_operator(int operator_type, double* value_1, double* value_2) {
  double result = 0.0;

  if (operator_type == plusCalc)
    result = (*value_1) + (*value_2);

  else if (operator_type == minusCalc)
    result = (*value_1) - (*value_2);

  else if (operator_type == un_minus)
    result = -(*value_2);

  else if (operator_type == mullCalc)
    result = (*value_1) * (*value_2);

  else if (operator_type == delCalc)
    result = (*value_1) / (*value_2);

  else if (operator_type == modCalc)
    result = fmod((*value_1), (*value_2));

  else if (operator_type == scalCalc)
    result = pow((*value_1), (*value_2));

  return result;
}

/*  int main( ) { printf("123"); } */

/*

1) цифра, то он помещается в стек.

2) Если  знак бинарной операции,
    1️⃣ то из стека извлекаются два верхних
элемента и над ними выполняется операция,
 результат которой заносится в стек,
    2️⃣ унарная операция выполняется над
верхним элементом.

* --------------------------------------------------------------------------
❓Операнд — это сущность, с которой оператор❓
выполняет какие-либо действия. Выражение — это
последовательность операторов и операндов,
 выполняющая действия ниже в любой комбинации.

*/