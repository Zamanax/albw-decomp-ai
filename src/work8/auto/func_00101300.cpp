typedef unsigned char u8;typedef int s32;typedef unsigned int u32;typedef long long s64;
struct Config{u8 active,special;u8 pad2[0x16];s64 time;};
extern "C" Config data_00714998;
extern "C" s32 func_00102470();
extern "C" bool func_001023F8();
void func_00101300(){s32 t6 = func_00102470();
s32 t3 = t6;
Config* t4 = &data_00714998;
t4->time=(s64)(t3*10);u32 one=1;bool t5 = func_001023F8();
bool t1 = t5;
bool t0 = t1;
if(t0)t4->special=one;Config* t2 = t4;if(t2->special||0!=t4->time)t4->active=1;}
