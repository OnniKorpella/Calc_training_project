#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QVector>
#include <QtMath>
#include <iostream>

#include "credit.h"
#include "debit.h"
#include "qcustomplot.h"
// #include "credittabl.h"

extern "C" {
#include "../Calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

  credit credit;
  debit  debit;

 private slots:
  void digits_numbers();
  void on_pushButton_dot_clicked();
  void operations();
  void on_pushButton_AC_clicked();
  void on_pushButton_equal_clicked();
  void math_operations();
  void on_action1_4_triggered();
  void on_pushButton_back_clicked();
  void digits_function();
  void on_pushButton_graf_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_debit_clicked();
};
#endif  // MAINWINDOW_H
