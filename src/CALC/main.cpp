#include "mainwindow.h"

// #include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow   w;

  //  QPushButton *button_quit = new QPushButton("quit");
  //  QObject::connect(button_quit, SIGNAL(clicked()), &a, SLOT(quit()));
  //  button_quit->show();

  w.show();
  return a.exec();
}
