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
  QCOMPARE(solution, output);
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
  QCOMPARE(solution, output);
}

void SudokuTest::firstUnsolvableTest() {
  QString input = "200260701"
                  "680070090"
                  "190004500"
                  "820100040"
                  "004602900"
                  "050003028"
                  "009300074"
                  "040050036"
                  "703018000";
  QString output = "not_solvable";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QCOMPARE(solution, output);
}

void SudokuTest::secondUnsolvableTest() {
  QString input = "200060701"
                  "680070090"
                  "190004500"
                  "820100040"
                  "004602900"
                  "050003028"
                  "009300074"
                  "240050036"
                  "703018000";
  QString output = "not_solvable";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QCOMPARE(solution, output);
}

void SudokuTest::thirdUnsolvableTest() {
  QString input = "000260701"
                  "680070090"
                  "196004500"
                  "820100040"
                  "004602900"
                  "050003028"
                  "009300074"
                  "040050036"
                  "703018000";
  QString output = "not_solvable";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QCOMPARE(solution, output);
}

void SudokuTest::forthUnsolvableTest() {
  QString input = "000260701"
                  "680070090"
                  "190004500"
                  "820100040"
                  "004602900"
                  "050003028"
                  "009300074"
                  "040050036"
                  "703018400";
  QString output = "not_solvable";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QCOMPARE(solution, output);
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
  QCOMPARE(solution, output);
}

void SudokuTest::firstHardTest() {
  QString input = "000600400"
                  "700003600"
                  "000091080"
                  "000000000"
                  "050180003"
                  "000306045"
                  "040200060"
                  "903000000"
                  "020000100";
  QString output = "581672439"
                   "792843651"
                   "364591782"
                   "438957216"
                   "256184973"
                   "179326845"
                   "845219367"
                   "913768524"
                   "627435198";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QCOMPARE(solution, output);
}

void SudokuTest::secondHardTest() {
  QString input = "200300000"
                  "804062003"
                  "013800200"
                  "000020390"
                  "507000621"
                  "032006000"
                  "020009140"
                  "601250809"
                  "000001002";
  QString output = "276314958"
                   "854962713"
                   "913875264"
                   "468127395"
                   "597438621"
                   "132596487"
                   "325789146"
                   "641253879"
                   "789641532";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QCOMPARE(solution, output);
}

void SudokuTest::thirdHardTest() {
  QString input = "020000000"
                  "000600003"
                  "074080000"
                  "000003002"
                  "080040010"
                  "600500000"
                  "000010780"
                  "500009000"
                  "000000040";
  QString output = "126437958"
                   "895621473"
                   "374985126"
                   "457193862"
                   "983246517"
                   "612578394"
                   "269314785"
                   "548769231"
                   "731852649";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QCOMPARE(solution, output);
}

void SudokuTest::randomTest() {
  QString input = "126437958"
                  "895621473"
                  "374985126"
                  "457193862"
                  "983246517"
                  "612578394"
                  "269314785"
                  "548769231"
                  "731852649";

  srand(time(nullptr));

  int blank_pos = rand() % 40 + 1;

  for (int i = 0; i < blank_pos; i++)
    input[rand() % 81] = QChar('0');
  QString output = "126437958"
                   "895621473"
                   "374985126"
                   "457193862"
                   "983246517"
                   "612578394"
                   "269314785"
                   "548769231"
                   "731852649";
  Sudoku *instance = new Sudoku(input);
  QString solution = instance->resolve();
  QCOMPARE(solution, output);
}

QTEST_MAIN(SudokuTest)
