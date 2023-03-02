#ifndef DEBIT_H
#define DEBIT_H

#include <QWidget>

namespace Ui {
class debit;
}

class debit : public QWidget {
  Q_OBJECT

 public:
  explicit debit(QWidget *parent = nullptr);
  ~debit();

  bool boolCapital = false;
  bool boolPlus    = false;
  bool boolMinus   = false;

  double boxPeriod      = 12;
  double boxPeriodPlus  = 0;
  double boxPeriodMinus = 0;

 private slots:
  void on_pushStart_clicked();
  void on_checkCapital_stateChanged(int arg1);
  void on_pushButton_2_clicked();
  //  void on_checkPlus_stateChanged(int arg1);
  //  void on_checkMinus_stateChanged(int arg1);
  void on_comboBoxPeriod_activated(int index);
  void on_comboBoxPlus_activated(int index);
  void on_comboBoxMinus_activated(int index);

 private:
  Ui::debit *ui;
};

#endif  // DEBIT_H
