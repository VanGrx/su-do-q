#include "mainwindow.h"
#include "ui_mainwindow.h"

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
      lineEdit->setStyleSheet("background: #FFFFFF;");
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
  menu->setFixedWidth(350);
  menu->setStyleSheet("border-color: black;border-style: solid; "
                      "border-width: 2px; background: #D4D4D4;");

  QVBoxLayout *menuLayout = new QVBoxLayout(menu);
  menuLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);

  QLabel *menu_title = new QLabel("SUDOKU SOLVER");
  menu_title->setAlignment(Qt::AlignmentFlag::AlignHCenter);
  menu_title->setWordWrap(true);
  menu_title->setFont(littleFont);
  menu_title->setStyleSheet("border-style: none;");
  menuLayout->addWidget(menu_title);

  QFrame *menu_line = new QFrame();
  menu_line->setFrameShape(QFrame::HLine);
  menuLayout->addWidget(menu_line);

  QPushButton *matrix_lock = new QPushButton("Lock the input");
  matrix_lock->setFixedSize(200, 50);
  menuLayout->addWidget(matrix_lock);

  QObject::connect(matrix_lock, SIGNAL(clicked()), this, SLOT(lock_toggle()));

  QSpacerItem *spacer = new QSpacerItem(1, 400);

  menuLayout->addSpacerItem(spacer);

  horizontalLayout->addWidget(menu);
}

void MainWindow::lock_toggle() {
  locked = !locked;
  QString color = "color: #000000;";
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (locked)
        color = "color: #FF0000;";

      matrix[i][j]->setStyleSheet(matrix[i][j]->styleSheet() + color);
      matrix[i][j]->setReadOnly(locked);
    }
  }
}

MainWindow::~MainWindow() { delete ui; }
