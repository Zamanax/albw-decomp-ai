#include "../../range.h"

#include "timer.h"
struct S{u8 pad[0x968];Timer timer;u8 other;u8 flag;void func_004FC07C(s32,s32,s32);void func_0012A0EC();};void S::func_0012A0EC(){timer.start(300);flag=0;func_004FC07C(5,-1,0);}
