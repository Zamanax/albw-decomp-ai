typedef unsigned char undefined;
typedef unsigned int undefined4;
extern char data_0070B800[];
extern undefined func_0012C718(unsigned char *);
extern undefined func_001B6D40(unsigned char *);
extern undefined func_004B964C(unsigned char *);
extern int func_0012E794();
static char *endIter(char *node, int const *off) { return node - *off; }
static inline int different(char *a, char *b) { return a != b; }
void func_0047F1CC(unsigned char *param_1)

{
  func_0012C718(param_1 + 0x98);
  int delta = *(int *)(param_1 + 0x54);
  for (int cursor = *(int *)(param_1 + 0x4c);
       cursor = cursor - delta, different((char *)cursor, endIter((char *)param_1 + 0x48, (int *)(param_1 + 0x54)));
       cursor = *(int *)(cursor + delta + 4)) {
    func_0012C718((unsigned char *)cursor);
  }
  func_001B6D40(param_1);
  func_004B964C(param_1);
  func_0012E794(*((undefined4 *)data_0070B800));
  return;
}
