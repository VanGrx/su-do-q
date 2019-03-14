#include "sudokutest.h"

void SudokuTest::firstSimpleTest() {
  QString input = "000260701"
                  "680070090"
                  "190004500"
                  "820100040"
                  "004602900"
                  "050003028"
                  "009300074"
                  "040050036"
                  "703018000";
  QString output = "435269781"
                   "682571493"
                   "197834562"
                   "826195347"
                   "374682915"
                   "951743628"
                   "519326874"
                   "248957136"
                   "763418259";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QVERIFY(solution.compare(output) == 0);
}

void SudokuTest::secondSimpleTest() {
  QString input = "100489006"
                  "730000040"
                  "000001295"
                  "007120600"
                  "500703008"
                  "006095700"
                  "914600000"
                  "020000037"
                  "800512004";
  QString output = "152489376"
                   "739256841"
                   "468371295"
                   "387124659"
                   "591763428"
                   "246895713"
                   "914637582"
                   "625948137"
                   "873512964";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QVERIFY(solution.compare(output) == 0);
}

void SudokuTest::firstIntermediateTest() {
  QString input = "020608000"
                  "580009700"
                  "000040000"
                  "370000500"
                  "600000004"
                  "008000013"
                  "000020000"
                  "009800036"
                  "000306090";
  QString output = "123678945"
                   "584239761"
                   "967145328"
                   "372461589"
                   "691583274"
                   "458792613"
                   "836924157"
                   "219857436"
                   "745316892";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QVERIFY(solution.compare(output) == 0);
}

QTEST_MAIN(SudokuTest)
