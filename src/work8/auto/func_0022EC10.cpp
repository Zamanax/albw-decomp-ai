typedef unsigned int u32;
typedef int s32;
typedef short s16;
typedef float f32;
typedef unsigned char u8;


#include "sead_string.h"
namespace sead {

}

struct Actor;
s32 func_00588BE4(Actor* a);
void func_00150A84(Actor* a, const sead::SafeString& name, s32 v);
extern const s32 data_006939C4;

struct Sub500 { char p0[8]; s16 m8; };
struct Actor {
    char p0[0x500];
    Sub500 m500;
};

extern "C" void func_0022EC10(Actor* self) {
    if (self->m500.m8 <= 0) {
        if (func_00588BE4(self) == data_006939C4) {
            func_00150A84(self, sead::SafeString("SE_Ku_V_DIE"), 0);
        } else {
            func_00150A84(self, sead::SafeString("SE_Zora_V_DIE"), 0);
        }
    } else {
        if (func_00588BE4(self) == data_006939C4) {
            func_00150A84(self, sead::SafeString("SE_Ku_V_DAMAGE"), 0);
        } else {
            func_00150A84(self, sead::SafeString("SE_Zora_V_DAMAGE"), 0);
        }
    }
}
