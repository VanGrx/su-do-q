#ifndef MYFUNC_H
#define MYFUNC_H
#include <chrono>
#include <iostream>

struct Timer {
  std::chrono::high_resolution_clock::time_point start, end;
  std::chrono::duration<float> duration;
  Timer() { start = std::chrono::high_resolution_clock::now(); }
  ~Timer() {
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float ms = duration.count() * 1000.0f;
    std::cout << ms << "ms\n";
  }
};

#endif // MYFUNC_H
