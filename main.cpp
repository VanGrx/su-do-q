#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// ERROR CHECK
void errorFatalImpl(const char *userMsg, const char *fileName,
                    const char *functionName, const int lineNum) {
  perror(userMsg);
  fprintf(stderr, "File: '%s'\nFunction: '%s'\nLine: '%d'\n", fileName,
          functionName, lineNum);
  exit(EXIT_FAILURE);
}
#define errorFatal(userMsg)                                                    \
  errorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define assertExpr(expr, userMsg)                                              \
  do {                                                                         \
    if (!(expr))                                                               \
      errorFatal(userMsg);                                                     \
  } while (0)

// ErrorCheck

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
