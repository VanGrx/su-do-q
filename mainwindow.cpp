#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QHBoxLayout *horizontalLayout = new QHBoxLayout(ui->centralwidget);

  // Initialization of sudoku GUI part
  QWidget *sudoku = new QWidget();
  sudoku->setStyleSheet("border-color: black;border-style: solid; "
                        "border-width: 2px; background: #F4D4F3;");
  sudoku->setFixedSize(75 * 9, 75 * 9);

  QGridLayout *layout = new QGridLayout(sudoku);

  QLineEdit *matrix[9][9];

  QFont littleFont("Courier New", 48);
  int h_line_count = 0;
  for (int i = 0; i < 11; ++i) {
    if (i % 4 == 3) {
      h_line_count++;
      QFrame *line = new QFrame();
      line->setFrameShape(QFrame::HLine);
      line->setMidLineWidth(10);
      layout->addWidget(line, i, 0, 1, 11);
      continue;
    }
    int v_line_count = 0;
    for (int j = 0; j < 11; j++) {
      if (j % 4 == 3) {
        v_line_count++;
        QFrame *line = new QFrame();
        line->setFrameShape(QFrame::VLine);
        line->setMidLineWidth(10);
        layout->addWidget(line, 0, j, 11, 1);
        continue;
      }

      QLineEdit *lineEdit = new QLineEdit(this);
      lineEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
      lineEdit->setMaxLength(1);
      lineEdit->setFixedSize(51, 51);
      lineEdit->setFont(littleFont);
      lineEdit->setStyleSheet("background: #FFFFFF");
      matrix[i - h_line_count][j - v_line_count] = lineEdit;
      layout->addWidget(lineEdit, i, j);
    }
  }
  sudoku->setLayout(layout);
  horizontalLayout->setSpacing(50);
  horizontalLayout->setMargin(50);
  horizontalLayout->addWidget(sudoku);

  // Initialization of menu GUI part
  QWidget *menu = new QWidget();
  menu->setStyleSheet("border-color: black;border-style: solid; "
                      "border-width: 2px; background: #D4D4D4;");

  QVBoxLayout *menuLayout = new QVBoxLayout(menu);
  menuLayout->setAlignment(Qt::AlignmentFlag::AlignCenter |
                           Qt::AlignmentFlag::AlignTop);

  QLabel *menu_title = new QLabel("SUDOKU\nSOLVER");
  menu_title->setFont(littleFont);
  menu_title->setStyleSheet("border-style: none;");
  menuLayout->addWidget(menu_title);

  horizontalLayout->addWidget(menu);
}

MainWindow::~MainWindow() { delete ui; }
