/**
 * @file Credit.c
 * @author nellyole (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../Calc.h"
/**
 * @brief Кредитный калькулятор, дифференцированные платежи
 *
 * @param sum                 сумма кредита
 * @param period              срок кредитования в месяцах
 * @param rate                процентная ставка
 * @param payType             тип платежей аннуитетные или дифференцированные
 * @param monthlyPaymentFirst платеж по кредиту (для дифференцированных платежей - первый)
 * @param monthlyPaymentLast  для дифференцированных платежей - последний платеж
 * @param overPayment         переплата
 * @param finalSum            финальная сумма
 */
void CreditCalc(double sum, double period, double rate, int payType, double* monthlyPaymentFirst, double* monthlyPaymentLast, double* overPayment, double* finalSum) {
  double monthlyRate;
  monthlyRate = rate / (100 * 12);
  if (payType == 0) {  // Аннуитетные иначе Дифференцированные
    *monthlyPaymentLast = sum * (monthlyRate / (1 - pow((1 + monthlyRate), -(period))));
    *finalSum           = *monthlyPaymentLast * period;
    *overPayment        = *finalSum - sum;
  } else {  // 30.42 в среднем дней в году. 30,42/365 = 0,083333333
    double percent;
    double sumBalance = sum;
    *overPayment      = 0;

    for (int i = 1; sumBalance > 0; i++) {
      percent    = sumBalance * ((rate / 100) * 0.08333333);
      sumBalance = sumBalance - (sum / period);
      *overPayment += percent;
      *monthlyPaymentLast = sum / period + percent;
      *finalSum           = sum + *overPayment;
      if (i == 1) *monthlyPaymentFirst = *monthlyPaymentLast;
    }
  }
}
  // месячная процентная ставка (рассчитывается как ставка по кредиту /100 *12)
  // ежемесячный платеж
  // переплата по кредиту double
  // общая сумма выпаченная по кредиту