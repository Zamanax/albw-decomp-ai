typedef unsigned char undefined1;
extern void* data_00712F70;
extern char* data_00709DF8;
extern void FUN_001b6d40(undefined1 *);
extern void FUN_0012c718(undefined1 *);
extern void FUN_0014b1d4(void*, int, int);
extern void FUN_004277dc(int);
static char* endIter(char*node,int const*off){return node-*off;}
static inline int different(char*a,char*b){return a!=b;}
void FUN_0047000c(undefined1 *param_1)
{
  int* pp = (int*)param_1;
  FUN_001b6d40(param_1);
  if (data_00712F70) FUN_0014b1d4(data_00712F70, 0, 1);
  if (data_00709DF8) data_00709DF8[0x65] = 1;
  int delta=pp[0x54/4];
  for(int cursor=pp[0x4c/4];cursor=cursor-delta,different((char*)cursor,endIter((char*)param_1+0x48,(int*)(param_1+0x54)));cursor=*(int*)(cursor+delta+4)){FUN_0012c718((undefined1*)cursor);}
  pp[0x18/4] &= ~0x80u;
  FUN_004277dc(pp[0x98/4]);
}
