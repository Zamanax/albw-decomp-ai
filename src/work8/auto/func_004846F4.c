typedef unsigned char undefined1;

extern void func_0012C718(undefined1 *);
extern void func_001B6D40(undefined1 *);

static char* endIter(char*node,int const*off){return node-*off;}
static inline int different(char*a,char*b){return a!=b;}

void func_004846F4(undefined1 *param_1)
{
  func_001B6D40(param_1);
  int delta=*(int*)(param_1+0x54);
  for(int cursor=*(int*)(param_1+0x4c);cursor=cursor-delta,different((char*)cursor,endIter((char*)param_1+0x48,(int*)(param_1+0x54)));cursor=*(int*)(cursor+delta+4)){
    func_0012C718((undefined1*)cursor);
  }
}
