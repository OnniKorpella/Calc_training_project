/**
 * @file Notation.c
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
 * @brief         Функция преобразования в постфиксную запись
 *
 * @param Input   Входящий список
 * @param Stack   Промежуточный список для сортировки
 * @param Exit    Выходящие список в постфиксной записи
 * @return        0 в случае успеха
 */
int Notation(stack** Input, stack** Stack, stack** Exit) {
  stack* Inpos = *Input;

  while (Inpos != NULL) {        // [1]
    if (Inpos->priority == 0) {  // 1.
      Push(Exit, 32, Inpos->number, Inpos->type, Inpos->priority);
      Pop(Input);
    }

    if (Inpos->type >= 3 && Inpos->type <= 17) {                                                                // 3
      while (Inpos != NULL && (*Stack) != NULL && (*Stack)->priority >= Inpos->priority && Inpos->type != 7) {  // 3.1
        Push(Exit, (*Stack)->str, (*Stack)->number, (*Stack)->type, (*Stack)->priority);
        Pop(Stack);
      }
      Push(Stack, Inpos->str, Inpos->number, Inpos->type, Inpos->priority);  // 3.2
      Pop(Input);
    }

    if (Inpos->type == 18) {  // 4
      Push(Stack, Inpos->str, Inpos->number, Inpos->type, Inpos->priority);
      Pop(Input);
    }

    if (Inpos->type == 19) {                           // 5
      while (Stack != NULL && (*Stack)->type != 18) {  // 5,1
        Push(Exit, (*Stack)->str, (*Stack)->number, (*Stack)->type, (*Stack)->priority);
        Pop(Stack);
      }
      Pop(Stack);
      Pop(Input);
    }
    Inpos = Inpos->next;
  }

  if (Inpos == NULL && Exit != NULL) {  // [2]
    while ((*Stack)) {                  // 1
      Push(Exit, (*Stack)->str, (*Stack)->number, (*Stack)->type, (*Stack)->priority);
      Pop(Stack);
    }
  }
  FreeStack(Inpos);
  return 0;
}
