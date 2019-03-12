#ifndef SUDOKU_H
#define SUDOKU_H
#include "matrix.h"
#include <QString>

class Sudoku {
private:
  std::vector<Matrix> calculation;

public:
  Sudoku();
  Sudoku(QString input_numbers);
  QString resolve();
};

#endif // SUDOKU_H
