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

  QFont defaultFont("Arial", 30);
  int h_line_count = 0;

  for (int i = 0; i < 11; ++i) {
    if (i % 4 == 3) {
      h_line_count++;
      QFrame *line = new QFrame();
      line->setFrameShape(QFrame::HLine);
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
      lineEdit->setFixedSize(60, 60);
      lineEdit->setFont(defaultFont);
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
  menu_title->setFont(defaultFont);
  menu_title->setStyleSheet("border-style: none;");
  menuLayout->addWidget(menu_title);

  QFrame *menu_line = new QFrame();
  menu_line->setFrameShape(QFrame::HLine);
  menuLayout->addWidget(menu_line);

  matrix_lock = new QPushButton("Lock the input");
  matrix_lock->setFixedSize(200, 50);
  QObject::connect(matrix_lock, SIGNAL(clicked()), this, SLOT(lock_toggle()));
  menuLayout->addWidget(matrix_lock);

  sudoku_solve = new QPushButton("Solve it!");
  sudoku_solve->setFixedSize(200, 50);
  QObject::connect(sudoku_solve, SIGNAL(clicked()), this, SLOT(solve_sudoku()));
  menuLayout->addWidget(sudoku_solve);

  QSpacerItem *spacer = new QSpacerItem(1, 400);
  menuLayout->addSpacerItem(spacer);

  horizontalLayout->addWidget(menu);
}

void MainWindow::lock_toggle() {
  locked = !locked;
  QString color = locked ? "background: #EEEEEE;color: #FF0000;"
                         : "background: #FFFFFF;color: #000000;";
  if (locked)
    matrix_lock->setText("Unlock the input");
  else
    matrix_lock->setText("Lock the input");

  if (locked)
    current_numbers = "";
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      matrix[i][j]->setStyleSheet(matrix[i][j]->styleSheet() + color);
      matrix[i][j]->setReadOnly(locked);
      if (locked)
        current_numbers +=
            (matrix[i][j]->text().isEmpty() ? "0" : matrix[i][j]->text());
      else {
        QString s = current_numbers.at(i * 9 + j) == "0"
                        ? QString("")
                        : current_numbers.at(i * 9 + j);
        matrix[i][j]->setText(s);
      }
    }
  }
  std::cout << current_numbers.toStdString() << std::endl;
}

void MainWindow::solve_sudoku() {
  if (!locked)
    lock_toggle();

  Sudoku *instance = new Sudoku(current_numbers);
  QString solution = instance->resolve();
  update_solution(solution);
}

void MainWindow::update_solution(QString solution) {

  QString color_found = "background: #EEEEEE;color: #00AA00;";
  QString color_given = "background: #EEEEEE;color: #000000;";

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      QString color = solution.at(i * 9 + j) == current_numbers.at(i * 9 + j)
                          ? color_given
                          : color_found;
      matrix[i][j]->setStyleSheet(color);
      matrix[i][j]->setText(solution.at(i * 9 + j));
    }
  }
}

MainWindow::~MainWindow() { delete ui; }
