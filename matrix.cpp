#include "matrix.h"
#include <iterator>
#include <set>
#include <stdio.h>
#include <string.h>

#ifdef QT_DEBUG
#include "matrixdebug.h"
#endif

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
}
Matrix::~Matrix(){};

unsigned Matrix::getRemaining() { return m_remaining_empty; }
int Matrix::getStatus() const { return m_status; }

QString Matrix::getStringMatrix() const { return m_string_matrix; }
void Matrix::parseMatrixAsString() {
  m_string_matrix.clear();
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      m_string_matrix.append(m_solution_matrix[i][j] + '0');
    }
}

void Matrix::prepareMatrix() {
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      m_solution_matrix[i][j] = m_string_matrix.at(i * 9 + j).digitValue();
  m_remaining_empty = 81;
  initializePossibleMatrix();
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

void Matrix::findMinPossibilities() {
  int min_remaining = 9;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      if (static_cast<int>(m_possible_matrix[i][j].size()) < min_remaining &&
          static_cast<int>(m_possible_matrix[i][j].size()) > 1) {
        min_remaining = static_cast<int>(m_possible_matrix[i][j].size());
        min_x = i;
        min_y = j;
        min_poss = std::vector<int>(m_possible_matrix[i][j]);
      }
    }
  return;
}

void Matrix::setSolutionMatrix(int i, int j, int num) {
  m_solution_matrix[i][j] = num;
  m_remaining_empty--;
  updatePossibleMatrix(num, i, j);
}

void Matrix::updatePossibleMatrix(int num, int i, int j) {
  m_possible_matrix[i][j].clear();

  updateColumn(num, i, j);
  updateRow(num, i, j);
  updateBox(num, i, j);
}

void Matrix::updateColumn(int num, int i, int j) {
  for (int j1 = 0; j1 < 9; j1++) {
    if (j1 == j && m_solution_matrix[i][j1] != 0)
      continue;
    auto it = std::find(m_possible_matrix[i][j1].begin(),
                        m_possible_matrix[i][j1].end(), num);
    if (it != m_possible_matrix[i][j1].end()) { // found a hit -> delete it
      m_possible_matrix[i][j1].erase(it);
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
      m_possible_matrix[i1][j].erase(it);
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
          m_possible_matrix[boxX][boxY].erase(it);
        }
      }
    }
    boxY = boxY - 3;
  }
}

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

void Matrix::solveSingleElements() {
  unsigned int curr_empty = m_remaining_empty + 1;

  while (curr_empty != m_remaining_empty) {
    curr_empty = m_remaining_empty;

    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++) {
        if (m_possible_matrix[i][j].size() == 1 &&
            m_solution_matrix[i][j] == 0) {
          m_solution_matrix[i][j] = m_possible_matrix[i][j].front();
          updatePossibleMatrix(m_possible_matrix[i][j].front(), i, j);
          m_remaining_empty--;
        }
      }
  }

  printMatrix(m_solution_matrix);
  // printPossibleMatrix(m_solution_matrix, m_possible_matrix);

  parseMatrixAsString();

  if (isSolvable())
    if (m_remaining_empty == 0)
      m_status = Matrix::SOLVED;
    else {
      findMinPossibilities();
      m_status = Matrix::UNSOLVED;
    }
  else
    m_status = Matrix::UNSOLVABLE;
}
