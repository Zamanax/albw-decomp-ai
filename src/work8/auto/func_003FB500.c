#include "stdarg.h"
struct func_003FB500_out { unsigned int ptr; unsigned int size; };

void func_003FB500(struct func_003FB500_out* out, unsigned int* cur, unsigned int size, unsigned int align, ...) {
  va_list ap;
  va_start(ap, size);
  unsigned int p;
  if (size == 0) {
    p = 0;
  } else {
    unsigned int c = *cur + align;
    unsigned int m = align - 1;
    p = (c - 1) & ~m;
    *cur = p + size;
  }
  out->ptr = p;
  out->size = size;
  va_end(ap);
}
