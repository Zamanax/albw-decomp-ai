static inline int scanNeg(signed char* base, int n)
{
  int i = 0;
  do {
    signed char* p = base + i * 64;
    if (p[6] >= 0) {
      return 1;
    }
    i++;
  } while (i != n);
  return 0;
}
int func_005843F0(unsigned char* self)
{
  unsigned char* q = self + 4;
  return scanNeg((signed char*)q, 0x14);
}
