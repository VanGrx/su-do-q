#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sudoku.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <iostream>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void lock_toggle();
  void solve_sudoku();

private:
  Ui::MainWindow *ui;
  QLineEdit *matrix[9][9];
  QPushButton *matrix_lock;
  QPushButton *sudoku_solve;
  bool locked = false;
  QString current_numbers;
  void update_solution(QString solution);
};

#endif // MAINWINDOW_H
