#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void print_err(char *err, const char *fmt, ...) {
  va_list ap;

  if (!err) return;
  va_start(ap, fmt);
  vsnprintf(err, 256, fmt, ap);
  va_end(ap);
}

int main() {
  char err[256];
  print_err(err, "fcntl(F_GETFL): %s", "12345");
  printf("%s", err);
  int a = 12;
  if (!!a) {
    printf("hhhhhh");
  }
  return 0;
}