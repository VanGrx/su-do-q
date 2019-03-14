#include "matrix.h"
#include <stdio.h>
#include <string.h>

Matrix::Matrix(){};

void Matrix::createMatrixFromFile() {
  FILE *fRead;

  fRead = fopen("C:\\Git\\su-do-q\\numbers", "r");

  if (fRead == nullptr) {
    fclose(fRead);
    std::cerr << "Wrong path to file." << std::endl;
  }

  char num;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      fscanf(fRead, "%c", &num);
      m_string_matrix.append(num);
      m_solution_matrix[i][j] = num - '0';
    }
  fclose(fRead);
  printMatrix();

  /*
   * TODO : if a read char differs from 0, remove that number from row ,
  col, box ,and delete the list of possibilities from that cell
   *
  if (num != '0'){

  }
  */
}

void Matrix::printMatrix() {

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
}

void Matrix::parseMatrixAsString() {
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      m_string_matrix.append((char)m_solution_matrix[i][j]);
    }
}

QString Matrix::getStringMatrix() { return m_string_matrix; }
