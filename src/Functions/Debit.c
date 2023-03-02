/**
 * @file Debit.c
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
 * @brief Депозитный калькулятор
 *
 * @param capital           капитализация процентов 0/1
 * @param sum               сумма депозита
 * @param period            срок размещения
 * @param rate              процентная ставка
 * @param plusSum           пополнение
 * @param boxPeriodPlus     месяц пополнения
 * @param minusSum          снятие
 * @param boxPeriodMinus    месяц снятия
 * @param sumFin            сумма в конце срока размещения
 * @param percent           начисленные проценты
 * @param tax               сумма налога
 */
void CalcDebit(int capital, double sum, double period, double rate, double plusSum, double boxPeriodPlus, double minusSum, double boxPeriodMinus, double *sumFin, double *percent, double *tax) {
  *sumFin = sum;

  if (capital == 0 && plusSum == 0 && boxPeriodPlus == 0 && minusSum == 0 && boxPeriodMinus == 0) {
    *percent = *sumFin / 100 * rate / 12 * period;
    *sumFin += *percent;
  }

  if (capital == 1 && plusSum == 0 && boxPeriodPlus == 0 && minusSum == 0 && boxPeriodMinus == 0) {
    for (int i = 0; i < period; i++) {
      *percent = *sumFin * rate * (30.41666667 / 365) / 100;
      *sumFin += *percent;
    }
    *percent = *sumFin - sum;
  }

  if (capital == 0 && plusSum != 0 && boxPeriodPlus != 0 && minusSum == 0 && boxPeriodMinus == 0) {
    double srok_p = 0, percent_p = 0, sum_p = 0;
    srok_p = period;
    for (int i = period - boxPeriodPlus; i > 0; i -= boxPeriodPlus) {
      srok_p = srok_p - boxPeriodPlus;
      percent_p += plusSum / 100.0 * rate / 12.0 * srok_p;
      sum_p += plusSum;
    }
    *percent = (sum / 100.0 * rate / 12.0 * period) + percent_p;
    *sumFin  = sum + sum_p + *percent;
  }

  if (capital == 0 && plusSum == 0 && boxPeriodPlus == 0 && minusSum != 0 && boxPeriodMinus != 0) {
    double sum_m = sum, percent_m = 0;
    for (int i = period; i > 0; i -= boxPeriodMinus) {
      percent_m += sum_m / 100.0 * rate / 12.0 * boxPeriodMinus;
      *sumFin = sum_m + percent_m;
      sum_m -= minusSum;
    }
    *percent = percent_m;
  }

  if (capital == 1 && plusSum != 0 && boxPeriodPlus != 0 && minusSum == 0 && boxPeriodMinus == 0) {
    double res_percent = 0;
    int    cycle;
    if (fmod(period, boxPeriodPlus) == 0)
      cycle = period / boxPeriodPlus;
    else
      cycle = period / boxPeriodPlus + 1;

    for (int i = cycle; i > 0; i--) {
      if (i == 1 && fmod(period, boxPeriodPlus) != 0) boxPeriodPlus = fmod(period, boxPeriodPlus);
      for (int i = 1; i <= boxPeriodPlus; i++) {
        *percent = *sumFin * rate * (30.41666667 / 365) / 100;
        *sumFin += *percent;
        res_percent += *percent;
      }
      *sumFin += plusSum;
    }
    *sumFin -= plusSum;
    *percent = res_percent;
  }

  if (capital == 1 && plusSum == 0 && boxPeriodPlus == 0 && minusSum != 0 && boxPeriodMinus != 0) {
    double res_percent = 0;
    int    cycle;
    if (fmod(period, boxPeriodMinus) == 0)
      cycle = period / boxPeriodMinus;
    else
      cycle = period / boxPeriodMinus + 1;

    for (int i = cycle; i > 0; i--) {
      if (i == 1 && fmod(period, boxPeriodMinus) != 0) boxPeriodMinus = fmod(period, boxPeriodMinus);
      for (int i = 1; i <= boxPeriodMinus; i++) {
        *percent = *sumFin * rate * (30.41666667 / 365) / 100;
        *sumFin += *percent;
        res_percent += *percent;
      }
      *sumFin -= minusSum;
    }
    *sumFin += minusSum;
    *percent = res_percent;
  }
  if (*percent > 75000) *tax = (*percent - 75000) * 0.13;
}
