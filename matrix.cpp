#include "matrix.h"
#include <iterator>
#include <stdio.h>
#include <string.h>

Matrix::Matrix(){};

void Matrix::updatePossibleMatrix(int num, int i, int j) {
  for (int j1 = 0; j1 < 9;
       j1++) { // i1=3       //i1 =i  a j = 0,9 i onda j1 = j a i=0,9
    if (j1 == j || m_solution_matrix[i, j1] != 0)
      continue;
    auto it = std::find(m_possible_matrix[i][j1].begin(),
                        m_possible_matrix[i][j1].end(), num);
    if (it != m_possible_matrix[i][j1].end()) { // found a hit -> delete it
      m_possible_matrix[i][j1].erase(
          it); // check if remaining posibilities is 1 -> than insert and repeat
      if (m_possible_matrix[i][j1].size() == 1) {
        // TODO insert into field,than repeat update
        /*
         * can be done with threads :
         * 1st thread inserts the 1 number remaining in m_possible_matrix into
         * field,and continues not caring baout the other thread 2nd thread
         * starts from begining and repeats the function with the  inserted
         * number ^ eventually a third thread does what the 2nd does,and 2nd
         * continues on.. maybe: no mutex or semaphores needed? any memory
         * change in vector or matrix is a valid change.. maybe: race conditions
         * might cause problems
         */
      }
    }
  }
  for (int i1 = 0; i1 < 9; i1++) {
    if (i1 == i || m_solution_matrix[i1, j] != 0)
      continue;
    auto it = std::find(m_possible_matrix[i1][j].begin(),
                        m_possible_matrix[i1][j].end(), num);
    if (it != m_possible_matrix[i1][j].end()) { // found a hit -> delete it
      m_possible_matrix[i1][j].erase(
          it); // check if remaining posibilities is 1 -> than insert and repeat
      if (m_possible_matrix[i1][j].size() == 1) {
        // TODO insert into field,than repeat update
      }
    }
  }

  // box check
  int boxX = i <= 2 ? 2 : i <= 5 ? 3 : 6;
  int boxY = j <= 2 ? 2 : j <= 5 ? 3 : 6;

  for (int i1 = 0; i1 < 3; i1++, boxX++)
    for (int j1 = 0; j1 < 3; j1++, boxY++) {
      if (boxX == i || boxY == j || m_solution_matrix[boxX, boxY] != 0)
        continue;
      else {
        auto it = std::find(m_possible_matrix[boxX][boxY].begin(),
                            m_possible_matrix[boxX][boxY].end(), num);
        if (it !=
            m_possible_matrix[boxX][boxY].end()) { // found a hit -> delete it
          m_possible_matrix[boxX][boxY].erase(
              it); // check if remaining posibilities
                   // is 1 -> than insert and repeat
          if (m_possible_matrix[boxX][boxY].size() == 1) {
            // TODO insert into field,than repeat update
          }
        }
      }
    }
  printPossibleMatrix();
}

void Matrix::initializePossibleMatrix() {
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      for (int k = 1; k < 9; k++)
        m_possible_matrix[i][j].push_back(k);
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (m_solution_matrix[i][j] != 0) {
        updatePossibleMatrix(m_solution_matrix[i][j], i, j);
      }
}

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
  initializePossibleMatrix();
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

void Matrix::printPossibleMatrix() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      std::cout << m_solution_matrix[i][j] << " :  ";
      for (auto it : m_possible_matrix[i][j])
        std::cout << it << ",";
      std::cout << std::endl;
    }
  }
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
