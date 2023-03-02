#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_pushStart_clicked();

  void on_pushClear_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
