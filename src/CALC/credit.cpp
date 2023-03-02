#include "credit.h"

#include "mainwindow.h"
#include "ui_credit.h"

credit::credit(QWidget *parent) : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);

  ui->lineSum->setText("100000");
  ui->linePeriod->setText("12");
  ui->lineRate->setText("10");
  ui->radioAnn->setChecked(true);
  // ui->lebel_2->setStyleSheet("color: rgb(10, 10, 10)");
}

credit::~credit() { delete ui; }

void credit::on_pushStart_clicked() {
  QString qsum = ui->lineSum->text();
  double  sum  = qsum.toDouble();

  QString qperiod = ui->linePeriod->text();
  double  period  = qperiod.toDouble();

  QString qrate = ui->lineRate->text();
  double  rate  = qrate.toDouble();

  double mountlyPayFirst;
  double mountlyPayLast;
  double percentFinal;
  double sumFinal;
  bool   payType;

  if (ui->radioAnn->isChecked()) {
    payType = 0;
  } else {
    payType = 1;
  }
  if (sum >= 1000 && sum <= 100000000 && period > 0 && period <= 600 && rate > 0 && rate <= 70) {
    // credit_result_window = new creditTabl();
    CreditCalc(sum, period, rate, payType, &mountlyPayFirst, &mountlyPayLast, &percentFinal, &sumFinal);

    std::string strSumFinal  = std::to_string(sumFinal);
    char       *cstrSumFinal = new char[strSumFinal.length() + 1];
    strcpy(cstrSumFinal, strSumFinal.c_str());

    std::string strPercentFinal  = std::to_string(percentFinal);
    char       *cstrPercentFinal = new char[strPercentFinal.length() + 1];
    strcpy(cstrPercentFinal, strPercentFinal.c_str());

    std::string strMountlyPayFirst  = std::to_string(mountlyPayFirst);
    char       *cstrMountlyPayFirst = new char[strMountlyPayFirst.length() + 1];
    strcpy(cstrMountlyPayFirst, strMountlyPayFirst.c_str());

    std::string strMountlyPayLast  = std::to_string(mountlyPayLast);
    char       *cstrMountlyPayLast = new char[strMountlyPayLast.length() + 1];
    strcpy(cstrMountlyPayLast, strMountlyPayLast.c_str());

    ui->lineSumFinal->setText(cstrSumFinal);
    ui->linePercent->setText(cstrPercentFinal);
    if (ui->radioAnn->isChecked()) {
      ui->lineMountlyPay->setText(cstrMountlyPayLast);
    } else {
      ui->lineMountlyPay->setText(cstrMountlyPayFirst);
      ui->lineMountlyPay->setText(ui->lineMountlyPay->text() + "... ..." + cstrMountlyPayLast);
    }
    delete[] cstrMountlyPayFirst;
    delete[] cstrMountlyPayLast;
    delete[] cstrPercentFinal;
    delete[] cstrSumFinal;
  } else {
    ui->lineSumFinal->setText(" ");
    ui->lineMountlyPay->setText(" ");
    ui->linePercent->setText("Error");
  }
}

void credit::on_pushClear_clicked() {
  ui->lineSumFinal->setText(" ");
  ui->lineMountlyPay->setText(" ");
  ui->linePercent->setText(" ");
  ui->lineSum->setText("100000");
  ui->linePeriod->setText("12");
  ui->lineRate->setText("10");
}
