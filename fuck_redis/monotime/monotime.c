#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

typedef uint64_t monotime;

monotime (*getMonotonicUs)();

monotime getMonotonicUs_posix(int i) {
  i = 2000;
  return i + 4321;
}

void monotonicInit() {
  getMonotonicUs = getMonotonicUs_posix;
}

int main() {
  monotonicInit();
  printf("%lu", getMonotonicUs());
}