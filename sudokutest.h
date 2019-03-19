#ifndef SUDOKUTEST_H
#define SUDOKUTEST_H
#include "sudoku.h"
#include <QObject>
#include <QtTest/QtTest>

class SudokuTest : public QObject {
  Q_OBJECT

signals:

private slots:
  void initTestCase() { qDebug("Start Sudoku testing"); }
  void firstSimpleTest();
  void secondSimpleTest();
  void firstUnsolvableTest();
  void secondUnsolvableTest();
  void thirdUnsolvableTest();
  void forthUnsolvableTest();
  void firstIntermediateTest();
  void cleanupTestCase() { qDebug("Finish Sudoku testing"); }
};
#endif // SUDOKUTEST_H
