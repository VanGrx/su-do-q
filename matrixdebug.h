#ifndef MATRIXDEBUG_H
#define MATRIXDEBUG_H
#include "matrix.h"

void printPossibleMatrix(const int (&m_solution_matrix)[9][9],
                         const std::vector<int> (&m_possible_matrix)[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      std::cout << m_solution_matrix[i][j] << " :  ";
      for (auto it : m_possible_matrix[i][j])
        std::cout << it << ",";
      std::cout << std::endl;
    }
  }
}

void printMatrix(const int (&m_solution_matrix)[9][9]) {

  for (int i = 0; i < 9; i++) {
    if (i % 3 == 0 && i != 0) {
      std::cout << "_______________________" << std::endl;
    }
    for (int j = 0; j < 9; j++) {
      if (j % 3 == 0 && j != 0) {
        std::cout << " | ";
      }
      std::cout << m_solution_matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl << std::endl;
}

#endif // MATRIXDEBUG_H
