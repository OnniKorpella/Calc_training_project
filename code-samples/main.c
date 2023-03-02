// https://www.banki.ru/services/calculators/deposits/?amount=500000&currency=RUB&date=02.01.2023&rate=10&tax_rate=35&tax_rate_threshold=12.5&period=1Y&is_capitalized=1&capitalization_period=1M#calculate-result
#include "../src/Calc.h"

// #include<stdmem>

int main() {
  // stack *A    = NULL;  // 😈
  // stack *B    = NULL;  //
  // stack *Exit = NULL;

  // char str[] = "5-9*7";

  // // RemoveSpaces(str);
  // printf("INPUt = %s\n", str);

  // Validator(str);
  // // printf("I = %s\n", str);
  // // RemoveSpaces(str);

  // printf("%s Validator(str) = %d %s", BLUE_P, Validator(str), RESET);
  // Parser(&A, str);
  // PrintStack(A);

  // Reverse(&A, &B);         // переворачиваем стек А - результат в B
  // Notation(&B, &A, &Exit); /*  подаем B_Revers A -временный стек */
  // PrintStack(Exit);

  // printf("%s Calc(&Exit)  = %lf %s\n", BLUE_T, Calc(&Exit), RESET);

  // // display(str);

  // FreeStack(A);
  // FreeStack(B);
  // // FreeStack(Exit);

  double *res_sum = calloc(1, sizeof(double));
  double *dohod = calloc(1 , sizeof(double));
  double *nalog   = calloc(1 , sizeof(double));
  CalcDebit(1, 100000, 60, 10, 800, 1, 0, 0, res_sum, dohod, nalog);
  printf("sumFin  = \t%lf\n", *res_sum);
  printf("dohod   = \t%lf\n", *dohod);
  printf("taxFin  = \t%lf\n", *nalog);

  free(res_sum);
  free(dohod);
  free(nalog);

  return 0;
}
