extern void func_00110848(char *);
extern void func_004A1AD4(int *);
static char *endIter(char *node, int const *off) { return node - *off; }
static inline int different(char *a, char *b) { return a != b; }
void func_004A1CDC(char *param_1)
{
  char *self = param_1;
  int cursor = *(int *)(param_1 + 0x48);
  int delta = *(int *)(param_1 + 0x50);
  for (; cursor = cursor - delta, different((char *)cursor, endIter((char *)param_1 + 0x44, (int *)(param_1 + 0x50))); cursor = *(int *)(cursor + delta + 4)) {
    func_00110848((char *)cursor);
  }
  {
    int i;
    for (i = 0; i < *(int *)(self + 0x3c); i++)
      func_004A1AD4((int *)(*(char **)(self + 0x38) + i * 12));
  }
}
