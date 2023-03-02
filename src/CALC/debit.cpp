#include "debit.h"

#include "mainwindow.h"
#include "ui_debit.h"

debit::debit(QWidget *parent) : QWidget(parent), ui(new Ui::debit) {
  ui->setupUi(this);

  ui->lineSum->setText("1000");
  //  ui->linePeriod->setText("12");
  ui->linePersentRate->setText("10");

  //  ui->linePlusMonth->setText("0");
  ui->linePlus->setText("0");
  //  ui->lineMinusMonth->setText("0");
  ui->lineMinus->setText("0");
  ui->comboBoxMinus->setCurrentIndex(0);
  ui->comboBoxPlus->setCurrentIndex(0);
  ui->comboBoxPeriod->setCurrentIndex(3);
}

debit::~debit() { delete ui; }

void debit::on_checkCapital_stateChanged(int arg1) {
  if (arg1 == Qt::Checked) {
    boolCapital = true;
  } else {
    boolCapital = false;
  }
}

// void debit::on_checkPlus_stateChanged(int arg1) {
//   if (arg1 == Qt::Checked) {
//     boolPlus = true;
//   } else {
//     boolPlus = false;
//   }
// }

// void debit::on_checkMinus_stateChanged(int arg1) {
//   if (arg1 == Qt::Checked) {
//     boolMinus = true;
//   } else {
//     boolMinus = false;
//   }
// }

void debit::on_pushStart_clicked() {
  QString qsum = ui->lineSum->text();
  double  sum  = qsum.toDouble();
  //  QString qperiod      = ui->linePeriod->text();
  //  double  period       = qperiod.toDouble();
  QString qrate = ui->linePersentRate->text();
  double  rate  = qrate.toDouble();
  QString qplus = ui->linePlus->text();
  double  plus  = qplus.toDouble();
  // QString qplus_month  = ui->linePlusMonth->text();
  // double  plus_month   = qplus_month.toDouble();
  QString qminus = ui->lineMinus->text();
  double  minus  = qminus.toDouble();
  // QString qminus_month = ui->lineMinusMonth->text();
  // double  minus_month  = qminus_month.toDouble();
  qDebug() << "qminus" << qminus;
  qDebug() << "minus" << minus;
  qDebug() << "boxPeriodMinus" << boxPeriodMinus;
  qDebug() << "boxPeriodPlus" << boxPeriodPlus;
  qDebug() << "boxPeriod" << boxPeriod;

  double sumFinal     = 0;
  double percentFinal = 0;
  double nalogFinal   = 0;
  bool   capital      = 0;
  if (sum >= 1000 && sum <= 100000000 && boxPeriod >= 1 && boxPeriod <= 18250 && rate > 0 && rate <= 999 && plus >= 0 && plus <= 100000000 && boxPeriodPlus >= 0 && boxPeriodPlus <= boxPeriod && minus >= 0 && minus <= (sum + plus) && boxPeriodMinus >= 0 && boxPeriodMinus <= boxPeriod) {
    CalcDebit(boolCapital, sum, boxPeriod, rate, plus, boxPeriodPlus, minus, boxPeriodMinus, &sumFinal, &percentFinal, &nalogFinal);
    qDebug() << "percentFinal" << percentFinal;
    qDebug() << "nalogFinal" << nalogFinal;
    std::string strSumFinal  = std::to_string(sumFinal);
    char       *cstrSumFinal = new char[strSumFinal.length() + 1];
    strcpy(cstrSumFinal, strSumFinal.c_str());

    std::string strPercentFinal  = std::to_string(percentFinal);
    char       *cstrPercentFinal = new char[strPercentFinal.length() + 1];
    strcpy(cstrPercentFinal, strPercentFinal.c_str());

    std::string strNalogFinal  = std::to_string(nalogFinal);
    char       *cstrNalogFinal = new char[strNalogFinal.length() + 1];
    strcpy(cstrNalogFinal, strNalogFinal.c_str());

    ui->lineFinalSum->setText(cstrSumFinal);
    ui->lineFinalPercent->setText(cstrPercentFinal);
    ui->lineFinalTax->setText(cstrNalogFinal);

    delete[] cstrSumFinal;
    delete[] cstrPercentFinal;
    delete[] cstrNalogFinal;
  } else {
    ui->lineFinalSum->setText(" ");
    ui->lineFinalPercent->setText(" ");
    ui->lineFinalTax->setText("Error");
  }
}

void debit::on_pushButton_2_clicked() {
  ui->lineFinalPercent->setText(" ");
  ui->lineFinalSum->setText(" ");
  ui->lineFinalTax->setText(" ");
  ui->lineSum->setText("1000");
  //  ui->linePeriod->setText("12");
  ui->linePersentRate->setText("10");
  //  ui->linePlusMonth->setText("0");
  ui->linePlus->setText("0");
  //  ui->lineMinusMonth->setText("0");
  ui->lineMinus->setText("0");
  ui->comboBoxPeriod->setCurrentIndex(3);
  ui->comboBoxMinus->setCurrentIndex(0);
  ui->comboBoxPlus->setCurrentIndex(0);
}

void debit::on_comboBoxPeriod_activated(int index) {
  if (index == 0) boxPeriod = 1;
  if (index == 1) boxPeriod = 3;
  if (index == 2) boxPeriod = 6;
  if (index == 3) boxPeriod = 12;
  if (index == 4) boxPeriod = 24;
  if (index == 5) boxPeriod = 36;
  if (index == 6) boxPeriod = 48;
  if (index == 7) boxPeriod = 60;
}

void debit::on_comboBoxPlus_activated(int index) {
  if (index == 0) boxPeriodPlus = 0;
  if (index == 1) boxPeriodPlus = 12;
  if (index == 2) boxPeriodPlus = 6;
  if (index == 3) boxPeriodPlus = 3;
  if (index == 4) boxPeriodPlus = 1;
}

void debit::on_comboBoxMinus_activated(int index) {
  if (index == 0) boxPeriodMinus = 0;
  if (index == 1) boxPeriodMinus = 12;
  if (index == 2) boxPeriodMinus = 6;
  if (index == 3) boxPeriodMinus = 3;
  if (index == 4) boxPeriodMinus = 1;
}
