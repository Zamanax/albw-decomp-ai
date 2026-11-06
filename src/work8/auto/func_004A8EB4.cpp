#include "sead_string.h"

extern void* func_004A8D80(void* p);
extern "C" const char ro_0069476C[];  // "World"

struct Arg004A8EB4 {
    sead::SafeString a;  // +0x00 (vptr, mStringTop)
    u32 f08;
    u32 f0c;
    u32 f10;
    u32 f14;
    u32 f18;
    u32 f1c;
    u32 f20;
    u32 f24;
    u32 f28;
    sead::SafeString b;  // +0x2c
    u8 g34;
    u8 g35;
    u8 g36;
    u8 g37;
    u8 g38;

    Arg004A8EB4()
        : f08(0), f0c(0), f10(0x20), f14(0), f18(0), f1c(0), f20(0), f24(0), f28(0),
          b(ro_0069476C), g34(7), g35(4), g36(0), g37(0), g38(0) {}
};

void* func_004A8EB4(const sead::SafeString& path) {
    Arg004A8EB4 arg;
    arg.a = path;
    return func_004A8D80(&arg);
}
