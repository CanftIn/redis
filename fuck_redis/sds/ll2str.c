#include <stdio.h>
#include <stdlib.h>

#define LLONG_MAX  __LONG_LONG_MAX__
#define LLONG_MIN  (-__LONG_LONG_MAX__-1LL)

int sdsll2str(char *s, long long value) {
  char *p, aux;
  unsigned long long v;
  size_t l;

  /* Generate the string representation, this method produces
   * a reversed string. */
  if (value < 0) {
    /* Since v is unsigned, if value==LLONG_MIN, -LLONG_MIN will overflow. */
    if (value != LLONG_MIN) {
      v = -value;
    } else {
      v = ((unsigned long long)LLONG_MAX) + 1;
    }
  } else {
    v = value;
  }

  p = s;
  do {
    *p++ = '0' + (v % 10);
    v /= 10;
  } while (v);
  if (value < 0) *p++ = '-';

  /* Compute length and add null term. */
  l = p - s;
  *p = '\0';

  /* Reverse the string. */
  p--;
  while (s < p) {
    aux = *s;
    *s = *p;
    *p = aux;
    s++;
    p--;
  }
  return l;
}

int main() {
  char* s = "654321";
  //sdsll2str(s, 123456);
  printf("%s\n", s);
}