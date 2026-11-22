typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32; typedef unsigned long long u64;
extern "C" u32 func_00111A14(void);
void* f_300E2C(void) { u64 r = (u64)func_00111A14() + 4; return (void*)(u32)r; }
