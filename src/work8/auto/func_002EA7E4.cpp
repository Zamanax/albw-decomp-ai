#include "albw_types.h"

struct Obj {
    u8 pad[0x10000];
};

extern "C" void func_0068C794(f32*, f32, f32, f32, f32);
extern "C" void func_002EC1B8(void*, s32);
extern "C" u32 func_0058AB74(void*);
extern "C" u32 func_0058ACC8(void*, f32);
extern "C" void func_0036C09C(void*, s32);
extern "C" u32 func_0058A8F0(void*);
extern "C" f32 func_0058AA40(void*);
extern "C" void func_006640EC(void*, s32) __attribute__((notailcall));
extern "C" void* func_002F5CD4(void*, s32);
extern "C" void func_00360AD0(void*);

extern "C" void func_002EA7E4(Obj* self) {
    func_0068C794((f32*)((u8*)self + 0xd4c), 4.0f, 0.1f, 0.0f, 0.1f);
    func_002EC1B8(self, 1);
    if (func_0058AB74(self) == 0x1b) {
        if (func_0058ACC8(self, 30.0f)) {
            func_0036C09C((u8*)self + 0x964, 2);
        }
        if (func_0058ACC8(self, 78.0f)) {
            f32 fv = 0.033333335f;
            u8* a = (u8*)self + 0x800;
            u8* q = a + 0x30c;
            *(s32*)((u8*)self + 0xb10) = 30;
            *(f32*)(q + 8) = fv;
            *(s32*)((u8*)self + 0xb0c) = 0;
            void* p = func_002F5CD4(self, 0);
            if (p) func_00360AD0(p);
            return;
        }
        bool doChange;
        if (func_0058A8F0(self) == 0) {
            f32 v = func_0058AA40(self);
            doChange = v > 108.0f;
        } else {
            doChange = true;
        }
        if (doChange) func_006640EC((u8*)self + 0x8c8, 0xf);
    }
}
