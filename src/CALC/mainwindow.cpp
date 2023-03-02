#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));  // number  ▾
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));      // X 2
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));   // + 3
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digits_numbers()));  // + 4
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));   // * 5
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));    // / 6
  connect(ui->pushButton_scal, SIGNAL(clicked()), this, SLOT(digits_numbers()));   // ^ 7
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));    // m 8

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_function()));       // s 9
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_function()));       // c 10
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_function()));       // t 11
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_function()));      // C 12
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_function()));      // S 13
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_function()));      // T 14
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_function()));      // q 15
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_function()));        // l 16
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_function()));       // L 17
  connect(ui->pushButton_bracket_l, SIGNAL(clicked()), this, SLOT(digits_numbers()));  // ( 18
  connect(ui->pushButton_bracket_r, SIGNAL(clicked()), this, SLOT(digits_numbers()));  // ) 19

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(operations()));
  //  connect(ui->pushButton_sign, SIGNAL(clicked()), this, SLOT(operations()));

  //  connect(ui->pushButton_percent, SIGNAL(clicked()), this,
  //  SLOT(digits_numbers()));

  ui->pushButton_div->setCheckable(true);
  ui->pushButton_mult->setCheckable(true);
  ui->pushButton_minus->setCheckable(true);
  ui->pushButton_plus->setCheckable(true);

  ui->domain_min->setText("-10");
  ui->domain_max->setText("10");
  ui->domain_step->setText("0.1");
  ui->line_x->setText("0");
  ui->domain_min_x->setText("-10");
  ui->domain_min_y->setText("-10");
  ui->domain_max_x->setText("10");
  ui->domain_max_y->setText("10");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString      new_label;

  if (ui->result->text().contains(".") && button->text() == "0") {
    new_label = ui->result->text() + button->text();
  } else {
    new_label = (ui->result->text() + button->text());
  }
  ui->result->setText(new_label);
}

void MainWindow::digits_function() {
  QPushButton *button = (QPushButton *)sender();
  QString      new_label;
  new_label = ui->result->text() + button->text() + "(";
  ui->result->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked() { /*if (!(ui->result->text().contains('.')))*/
  ui->result->setText(ui->result->text() + ".");
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  double       all_numbers;
  QString      new_label;

  if (button->text() == "+/-") {
    all_numbers = (ui->result->text()).toDouble();
    all_numbers = all_numbers * -1;
    new_label   = QString::number(all_numbers, 'g', 9);

    ui->result->setText(new_label);
  }

  //  else if (button->text() == "%") {
  //    all_numbers = (ui->result->text()).toDouble();
  //    all_numbers = all_numbers * 0.01;
  //    new_label   = QString::number(all_numbers, 'g', 9);
  //  }

  ui->result->setText(new_label);
}

void MainWindow::math_operations() {
  QPushButton *button = (QPushButton *)sender();
  QString      input_str;

  input_str = ui->result->text() + button->text();

  ui->result->setText(input_str);
}

void MainWindow::on_pushButton_AC_clicked() {
  // ui->pushButton_1->setChecked(false);
  //  ui->line_x->clear();
  //  std::string res_str(" ");
  //  QString     label = QString::fromStdString(res_str);
  //  ui->line_x->setText(label);
  ui->line_x->setText("0");
}

void MainWindow::on_action1_4_triggered() { close(); }

void MainWindow::on_pushButton_back_clicked() {
  QString text1 = ui->result->text();
  text1.chop(1);

  if (text1.isEmpty()) {
    text1 = " ";
  }

  ui->result->setText(text1);

  QString text_x = ui->line_x->text();
  text_x.chop(1);

  if (text_x.isEmpty()) {
    text_x = " ";
  }

  ui->line_x->setText(text_x);
}

void MainWindow::on_pushButton_equal_clicked() {
  QString     input   = ui->result->text();
  std::string str     = input.toStdString();
  char       *cstr    = new char[str.length() + 1];
  QString     input_x = ui->line_x->text();
  std::string str_x   = input_x.toStdString();
  char       *cstr_x  = new char[str.length() + 1];
  std::string substr  = "x";
  strcpy(cstr_x, str_x.c_str());
  int    index = 0;
  size_t pos;

  if (Validator(cstr_x) != 0) {
    ui->line_x->clear();
    ui->line_x->setText("ERROR[00x]");
    QMessageBox::information(this, "ERROR", "ERROR[00x]");
  } else {
    while ((pos = str.find(substr)) != std::string::npos) {
      str.replace(pos, 1, cstr_x);
    }
  }
  strcpy(cstr, str.c_str());
  ui->line_x->clear();
  std::string res_str_x("");
  QString     label_x = QString::fromStdString(res_str_x);
  ui->line_x->setText(label_x);
  display(cstr_x);

  if (Validator(cstr) == 101) {
    ui->result->clear();
    // std::string res_str("ERROR");
    // QString     label = QString::fromStdString(res_str);
    ui->result->setText("[101]");
    QMessageBox::information(this, "ERROR", "[101]");

  } else if (Validator(cstr) == 102) {
    ui->result->setText("ERROR: [102]");
    QMessageBox::information(this, "ERROR", "🥸 [102]");
  } else if (Validator(cstr) == 103) {
    ui->result->setText("ERROR: [103]");
    QMessageBox::information(this, "ERROR", "[103]");
  } else if (Validator(cstr) == 104) {
    ui->result->setText("ERROR: [104]");
    QMessageBox::information(this, "ERROR", "[117]");
  } else if (Validator(cstr) == 105) {
    ui->result->setText("ERROR: [105]");
    QMessageBox::information(this, "ERROR", "[105]");
  } else if (Validator(cstr) == 106) {
    ui->result->setText("ERROR: точка [106]");
    QMessageBox::information(this, "ERROR", "точка [106]");
  } else if (Validator(cstr) == 107) {
    ui->result->setText("ERROR: [107]");
    QMessageBox::information(this, "ERROR", " два оператора подряд [107]");
  } else if (Validator(cstr) == 108) {
    ui->result->setText("ERROR[108]");
    QMessageBox::information(this, "ERROR", "пустые скобки  [117]");
  } else if (Validator(cstr) == 109) {
    ui->result->setText("ERROR:[109]");
    QMessageBox::information(this, "ERROR", " перед и после mod должно быть число [11mod1] [109]");
  } else if (Validator(cstr) == 110) {
    ui->result->setText("ERROR: [110]");
    QMessageBox::information(this, "ERROR", "перед цифрой ) [110]");
  } else if (Validator(cstr) == 111) {
    ui->result->setText("ERROR: [111]");
    QMessageBox::information(this, "ERROR", "перед функцией ) [111]");
  } else if (Validator(cstr) == 112) {
    ui->result->setText("ERROR: [112]");
    QMessageBox::information(this, "ERROR", " перед '(' число или точка [112]");
  } else if (Validator(cstr) == 113) {
    ui->result->setText("ERROR: [113]");
    QMessageBox::information(this, "ERROR", "[113]");
  } else if (Validator(cstr) == 114) {
    ui->result->setText("ERROR: [114]");
    QMessageBox::information(this, "ERROR", "error! 😡 [114]");
  } else if (Validator(cstr) == 115) {
    ui->result->setText("ERROR: [115]");
    QMessageBox::information(this, "ERROR", "[115]");
  } else if (Validator(cstr) == 116) {
    ui->result->setText("ERROR: [116]");
    QMessageBox::information(this, "ERROR", "степень [116]");
  } else if (Validator(cstr) == 117) {
    ui->result->setText("ERROR:[117]");
    QMessageBox::information(this, "ERROR", " error! 😡 [117]");
  } else if (Validator(cstr) == 118) {
    ui->result->setText("ERROR: [118]");
    QMessageBox::information(this, "ERROR", "error! 😡 [118]");
  } else if (Validator(cstr) == 119) {
    ui->result->setText("ERROR: [119]");
    QMessageBox::information(this, "ERROR", " nan 😡 [118]");
  } else if (Validator(cstr) == 120) {
    ui->result->setText("ERROR: [120]");
    QMessageBox::information(this, "ERROR", "скобки [120]");
  } else {
    display(cstr);
    ui->result->setText(cstr);
  }
  ui->line_x->setText("0");
  delete[] cstr;
  delete[] cstr_x;
}

void MainWindow::on_pushButton_graf_clicked() {
  ui->widget->clearGraphs();
  QString min       = ui->domain_min->text();    // min
  QString max       = ui->domain_max->text();    // max
  QString step      = ui->domain_step->text();   // step
  QString res_graph = ui->domain_res->text();    // res
  QString q_min_x   = ui->domain_min_x->text();  // min_x
  QString q_min_y   = ui->domain_min_y->text();  // min_y
  QString q_max_x   = ui->domain_max_x->text();  // max_x
  QString q_max_y   = ui->domain_max_y->text();  // max_y
  QString result    = ui->result->text();

  double x, y;
  double minDouble  = min.toDouble();
  double maxDouble  = max.toDouble();
  double stepDouble = step.toDouble();

  double d_min_x = q_min_x.toDouble();
  double d_min_y = q_min_y.toDouble();
  double d_max_x = q_max_x.toDouble();
  double d_max_y = q_max_y.toDouble();

  QVector<double> X, Y;

  // ui->widget->xAxis->setRange(minDouble, maxDouble);  // область видимости по х
  // ui->widget->yAxis->setRange(minDouble, maxDouble);  // область видимости по у
  ui->widget->xAxis->setRange(d_min_x, d_max_x);  // область видимости по х
  ui->widget->yAxis->setRange(d_min_y, d_max_y);  // область видимости по у

  if (minDouble < -100 || minDouble >= maxDouble || maxDouble > 100 || stepDouble < 0.01 || stepDouble > 10) {
    ui->domain_res->setText("ERROR");
  } else {
    for (x = minDouble; x <= maxDouble; x += stepDouble) {
      std::string str  = result.toStdString();  // строка с выражением уже в стринг
      std::string strx = std::to_string(x);     // min уже в стринг
      strx             = strx.replace(0, 0, "(");
      int strLen       = strx.length();
      strx             = strx.replace(strLen, strLen, ")");
      size_t pos;

      while ((pos = str.find("x")) != std::string::npos) {  // номер позиции икса пока не равен концу
        str.replace(pos, 1, strx);                          // в строку с выражением подстовляем вместо
                                                            // Х значение взятое с мин
      }

      char *cstr = new char[str.length() + 1];  //
      strcpy(cstr, str.c_str());                //

      X.push_back(x);
      Y.push_back(display_double(cstr));

      delete[] cstr;
    }

    ui->widget->addGraph();               // добавляем график на виджет
    ui->widget->graph(0)->addData(X, Y);  // передодим в аддДата х, у,// обращаемся к этому графику и
                                          // устfнавливаем ему значение
    ui->widget->replot();                 // функцией реплот нарисуем график
    ui->domain_res->setText(result);      // выводим текст с главного поля
    ui->line_x->clear();                  // удоляем данные с полей
    ui->result->clear();                  // удоляем данные с полей
  }
}

void MainWindow::on_pushButton_credit_clicked() { credit.show(); }

void MainWindow::on_pushButton_debit_clicked() { debit.show(); }
