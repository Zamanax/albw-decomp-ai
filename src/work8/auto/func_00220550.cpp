typedef unsigned char u8;
typedef int s32;
typedef float f32;
struct En { char pad0[0x8c5]; u8 m8c5; };
extern "C" bool func_005211BC(En* e, f32 a, f32 b);
extern "C" void func_004FABDC(En* e, s32 a, s32 b, s32 c);
extern "C" void func_004FC07C(En* e, s32 a, s32 b, s32 c);
extern "C" void func_0065E398(void*, s32) __attribute__((notailcall));
void f220550(En* e) {
    if (!func_005211BC(e, 20.0f, 0.0f)) {
        func_0065E398((char*)e + 0x8c0, 15);
        return;
    }
    s32 c = e->m8c5;
    if (c == 7) func_004FABDC(e, 5, 12, 0);
    else func_004FC07C(e, 5, 12, 0);
}
