#include "../Calc.h"
/**
 * @brief Фукция визуализации односвязного списка 
 * 
 * @param A Список для визуализации
 */
void PrintStack(const stack* A) {
  int x = 0;

  if (A != NULL) {
    printf(
        "%s⎧⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺"
        "⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺",
        GREEN);
    printf("%s\n", RESET);
    // printf("%s|\t%s[  addresses   ] ---->  ",
    // GREEN, BLUE_P); printf("str num(double)
    // type priority%s\n", RESET);
    printf("%s| \t  %s", GREEN, BLUE_P);
    printf("str\tnum(double)\t\ttype\tpriority%s\n", RESET);
    while (A != NULL) {
      // ----------------------------------------------------------------------
      printf("%s|", GREEN);
      printf("%d\t", x + 1);
      if (ispunct(A->str) || isalpha(A->str)) {
        printf("   %s%c", YELLOW, A->str);
        printf("   \t\t\t\t");
        printf("%s%d\t%d ", YELLOW, A->type, A->priority);
      }
      printf("   \t");
      if (!ispunct(A->str) && !isalpha(A->str)) {
        printf("%s%lf\t", GREEN, A->number);
        printf("   \t");
        printf("%s%d\t%d ", GREEN, A->type, A->priority);
      }
      printf("\n");
      // ----------------------------------------------------------------------
      A = A->next;
      x++;
    }
    printf("%s|%s size stack ", GREEN, YELLOW);
    printf("= %s %d%s\n", RED, x, RESET);
    printf(
        "%s⎩_____________________________________"
        "____",
        GREEN);
    printf("____________%s", RESET);
  }
  printf("\n");
}
