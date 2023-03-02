/**
 * @file Stack.c
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
 * @brief Функция для добавления данных в список
 * 
 * @param A         Список для добавления следующих данных
 * @param str       char показывает знак операции
 * @param num       Число 
 * @param type      Тип лексемы
 * @param priority  Приоритет лексемы
 */
void Push(stack** A, char str, double  num, int type, int priority) {
  stack* B    = malloc(sizeof(stack));
  B->str      = str;       
  B->number   = num;        
  B->type     = type;      
  B->priority = priority;  
  B->next     = *A;        
  *A          = B;         
}

/**
 * @brief Функция для удаления данных в списоке
 * 
 * @param A         Список для удаления следующих данных
 * @param str       char показывает знак операции
 * @param num       Число 
 * @param type      Тип лексемы
 * @param priority  Приоритет лексемы
 * @return          Возвращается модифицированный список
 */
int Pop(stack** A) {
  int res = OK;
  if ((*A) == NULL)
    res = FAIL;
  else {
    stack* B = NULL;
    B        = *A;
    *A       = (*A)->next;
    free(B);
  }
  return res;
}

/**
 * @brief Функция удаления стека
 * 
 * @param A         Список для удаления
 */
void FreeStack(stack* A) {
  while (A) {
    Pop(&A);
  }
}

/**
 * @brief Функция  для переворачивания списка
 * 
 * @param A Необходимо развернуть
 * @param B Перевернутый список
 */
void Reverse(stack** A, stack** B) {
  while ((*A) != NULL) {
    Push(B, (*A)->str, (*A)->number, (*A)->type, (*A)->priority);
    Pop(A);
  }
}
