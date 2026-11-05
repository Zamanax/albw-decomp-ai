typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

#include "sead_string.h"

void func_0066A8D8(void* p, u32 a);
void func_001507D8(void* self, const sead::SafeString& name, s32 v);

void func_004E4FA4(char* self) {
    char* i = *(char**)(*(char**)(self + 0x47c) + 0x14);
    if (*(u8*)(i + 0x1c) == 0) {
        if (*(f32*)(i + 0x10) >= 0.0f) {
            if (*(f32*)(i + 8) == *(f32*)(i + 0x14)) {
                self += 0x400;
                func_0066A8D8(self + 0x84, 7);
                return;
            }
        } else if (!(*(f32*)(i + 8) > 0.0f)) {
            self += 0x400;
            func_0066A8D8(self + 0x84, 7);
            return;
        }
    }
    func_001507D8(self, sead::SafeString("SE_BombL_FUSE"), 0);
}
