#include "matrix.h"
#include <iterator>
#include <set>
#include <stdio.h>
#include <string.h>
singlePosibility::singlePosibility(){};
singlePosibility::singlePosibility(int i, int j) : m_i(i), m_j(j){};
int singlePosibility::getI() const { return m_i; }
int singlePosibility::getJ() const { return m_j; }
void singlePosibility::setI(int i) { m_i = i; }
void singlePosibility::setJ(int j) { m_j = j; }

Matrix::Matrix(){};
Matrix::Matrix(QString input) : m_string_matrix(input) { prepareMatrix(); }
Matrix::Matrix(const Matrix &other) {
  m_remaining_empty = other.m_remaining_empty;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      m_solution_matrix[i][j] = other.m_solution_matrix[i][j];
      for (auto it : other.m_possible_matrix[i][j])
        m_possible_matrix[i][j].push_back(it);
    }
  m_string_matrix = other.m_string_matrix;
  for (auto it : other.m_store_possible)
    m_store_possible.push_back(it);
}

void Matrix::storeSinglePosibility(int i, int j) {
  // check if this index is already stored in vector of posibilities
  // if not store new coordinates for a single posibility
  auto iterator = std::find_if(m_store_possible.begin(), m_store_possible.end(),
                               [&i, &j](const singlePosibility &s) {
                                 return (i == s.getI()) && (j == s.getJ());
                               });
  if (iterator == m_store_possible.end())
    m_store_possible.push_back(singlePosibility(i, j));
}

singlePosibility Matrix::findMinPossibilityIndexes() {
  int min_remaining = 9;
  singlePosibility min_posibility_cell;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      if (static_cast<int>(m_possible_matrix[i][j].size()) < min_remaining &&
          static_cast<int>(m_possible_matrix[i][j].size()) > 1) {
        min_remaining = static_cast<int>(m_possible_matrix[i][j].size());
        min_posibility_cell.setI(i);
        min_posibility_cell.setJ(j);
      }
    }
  return min_posibility_cell;
}

void Matrix::setSolutionMatrix(int i, int j, int num) {
  m_solution_matrix[i][j] = num;
  updatePossibleMatrix(num, i, j);
}

// For begining of the possible matrix,insert '0', for 2nd element '1'
// If remaining matrix is bigger than 2 elements,can be redone 2 return more
// than 2
int Matrix::getPossibleMatrixValue(int i, int j, int pos) {
  return pos == 0 ? m_possible_matrix[i][j].front()
                  : m_possible_matrix[i][j].back();
}

void Matrix::prepareMatrix() {
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      m_solution_matrix[i][j] = m_string_matrix.at(i * 9 + j).digitValue();
  m_remaining_empty = 81;
  initializePossibleMatrix();
}

unsigned Matrix::getRemaining() { return m_remaining_empty; }

bool Matrix::isSolvable() {
  for (int i = 0; i < 9; i++) {
    std::set<int> numbers;
    for (int j = 0; j < 9; j++) {
      if (m_possible_matrix[i][j].empty() && m_solution_matrix[i][j] == 0)
        return false;
      if (m_solution_matrix[i][j] != 0) {
        if (numbers.count(m_solution_matrix[i][j]) == 0)
          numbers.insert(m_solution_matrix[i][j]);
        else
          return false;
      }
    }
  }

  for (int j = 0; j < 9; j++) {
    std::set<int> numbers;
    for (int i = 0; i < 9; i++) {
      if (m_solution_matrix[i][j] != 0) {
        if (numbers.count(m_solution_matrix[i][j]) == 0)
          numbers.insert(m_solution_matrix[i][j]);
        else
          return false;
      }
    }
  }

  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 3; i++) {
      int boxX = i * 3;
      int boxY = j * 3;
      std::set<int> numbers;
      for (int i1 = 0; i1 < 3; i1++, boxX++) {
        boxY = j * 3;
        for (int j1 = 0; j1 < 3; j1++, boxY++) {
          if (m_solution_matrix[boxX][boxY] != 0) {
            if (numbers.count(m_solution_matrix[boxX][boxY]) == 0)
              numbers.insert(m_solution_matrix[boxX][boxY]);
            else
              return false;
          }
        }
      }
    }
  }

  return true;
}

void Matrix::updateColumn(int num, int i, int j) {
  for (int j1 = 0; j1 < 9; j1++) {
    if (j1 == j && m_solution_matrix[i][j1] != 0)
      continue;
    auto it = std::find(m_possible_matrix[i][j1].begin(),
                        m_possible_matrix[i][j1].end(), num);
    if (it != m_possible_matrix[i][j1].end()) { // found a hit -> delete it
      m_possible_matrix[i][j1].erase(it);
      if (m_possible_matrix[i][j1].size() == 1) {
        storeSinglePosibility(i,
                              j1); // TODO insert into field,than repeat update
                                   /*
                                    * can be done with threads :
                                    * 1st thread inserts the 1 number remaining in m_possible_matrix
                                    * into
                                    * field,and continues not caring baout the other thread 2nd thread
                                    * starts from begining and repeats the function with the  inserted
                                    * number ^ eventually a third thread does what the 2nd does,and 2nd
                                    * continues on.. maybe: no mutex or semaphores needed? any memory
                                    * change in vector or matrix is a valid change.. maybe: race
                                    * conditions
                                    * might cause problems
                                    */
      }
    }
  }
}
void Matrix::updateRow(int num, int i, int j) {
  for (int i1 = 0; i1 < 9; i1++) {
    if (i1 == i && m_solution_matrix[i1][j] != 0)
      continue;
    auto it = std::find(m_possible_matrix[i1][j].begin(),
                        m_possible_matrix[i1][j].end(), num);
    if (it != m_possible_matrix[i1][j].end()) { // found a hit -> delete it
      m_possible_matrix[i1][j].erase(it); // check if remaining posibilities
                                          // is 1 -> than insert and repeat
      if (m_possible_matrix[i1][j].size() == 1) {
        // TODO insert into field,than repeat update
        storeSinglePosibility(i1, j);
      }
    }
  }
}
void Matrix::updateBox(int num, int i, int j) {
  int boxX = i <= 2 ? 0 : i <= 5 ? 3 : 6;
  int boxY = j <= 2 ? 0 : j <= 5 ? 3 : 6;

  for (int i1 = 0; i1 < 3; i1++, boxX++) {
    for (int j1 = 0; j1 < 3; j1++, boxY++) {
      if (m_solution_matrix[boxX][boxY] == 0 &&
          m_possible_matrix[boxX][boxY].empty() == false) {
        auto it = std::find(m_possible_matrix[boxX][boxY].begin(),
                            m_possible_matrix[boxX][boxY].end(), num);
        if (it !=
            m_possible_matrix[boxX][boxY].end()) { // found a hit -> delete it
          m_possible_matrix[boxX][boxY].erase(
              it); // check if remaining posibilities
                   // is 1 -> than insert and repeat
          if (m_possible_matrix[boxX][boxY].size() == 1) {
            storeSinglePosibility(boxX, boxY);

            // TODO insert into field,than repeat update
          }
        }
      }
    }
    boxY = boxY - 3;
  }
}

void Matrix::updatePossibleMatrix(int num, int i, int j) {
  m_possible_matrix[i][j].clear();

  updateColumn(num, i, j);
  updateRow(num, i, j);
  updateBox(num, i, j);
}

void Matrix::initializePossibleMatrix() {
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      for (int k = 1; k <= 9; k++)
        m_possible_matrix[i][j].push_back(k);
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (m_solution_matrix[i][j] != 0) {
        m_remaining_empty--;
        updatePossibleMatrix(m_solution_matrix[i][j], i, j);
      }
}

void Matrix::printPossibleMatrix() const {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      std::cout << m_solution_matrix[i][j] << " :  ";
      for (auto it : m_possible_matrix[i][j])
        std::cout << it << ",";
      std::cout << std::endl;
    }
  }
}

void Matrix::printMatrix() const {

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
  // printPossibleMatrix();
}

void Matrix::parseMatrixAsString() {
  m_string_matrix.clear();
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      m_string_matrix.append(m_solution_matrix[i][j] + '0');
    }
}

QString Matrix::getStringMatrix() const { return m_string_matrix; }

void Matrix::solveSingleElements() {
  while (m_store_possible.empty() == false) {
    int i = m_store_possible.front().getI();
    int j = m_store_possible.front().getJ();
    /*   std::cout << "Single element- i:" << i << " , j:" << j
                 << " ,number:" << m_possible_matrix[i][j].front() <<
       std::endl;*/
    m_store_possible.erase(m_store_possible.begin());
    m_solution_matrix[i][j] = m_possible_matrix[i][j].front();
    updatePossibleMatrix(m_possible_matrix[i][j].front(), i, j);
    m_remaining_empty--;
  }
  // No single posibilities remaining,but matrix is undone
  // Store current state of matrix in vector,and try to solve
  // Find least posibility cell ,and put one numbers than resolve

  /*if (m_remaining_empty != 0) {

      int min_remaining = 9;
      singlePosibility min_posibility_cell;
      for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
          if (static_cast<int>(m_possible_matrix[i][j].size()) <
     min_remaining)
      { min_remaining = static_cast<int>(m_possible_matrix[i][j].size());
            min_posibility_cell.setI(i);
            min_posibility_cell.setJ(j);
          }
        }
      // in case only 2 posibilities are remaining:
      Matrix *m1 = new Matrix(*this);

      int i = min_posibility_cell.getI();
      int j = min_posibility_cell.getJ();
      m_solution_matrix[i][j] = m_possible_matrix[i][j].front();
      m1->setSolutionMatrix(i, j, m_possible_matrix[i][j].back());
      updatePossibleMatrix(m_solution_matrix[i][j], i, j);
      Matrix::solveSingleElements();
      }
      */
  printMatrix();

  parseMatrixAsString();
}

Matrix::~Matrix(){};
