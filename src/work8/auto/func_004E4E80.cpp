#include "albw_types.h"
#include "sead_string.h"

void* func_004CF478(void* p, u32 a, u32 b);
void func_00151148(void* p, u32 a);
u32 func_002C11E8(void* buf, u32 id, u32 arg, u32 flag);
void func_0016898C(void* owner, u32 req);
void func_00588C14(void* self, u32 a, u32 b);
void func_00150A84(void* self, const sead::SafeString& s, s32 v);

struct AnimElem { char _pad[0x10]; f32 m10; };
struct AnimArr {
    char _pad[0xc];
    s32 mNum;
    s32 mMax;
    AnimElem* mData;
    AnimElem& operator[](s32 i) { if ((u32)i < (u32)mNum) return mData[i]; return mData[0]; }
};
struct Sub4C0 {
    u32 m0; u32 m4; f32 m8;
    void start(u32 n, u32 c = 0) { m4 = n; if (n) m8 = 1.0f / n; else m8 = 0.0f; m0 = c; }
};

void func_004E4E80(u8* self) {
    u8 buf[0x60];
    func_004CF478(*(void**)(self + 0x478), 1, 0);
    func_00151148(*(void**)(self + 0x4cc), 1);
    u32 r = func_002C11E8(buf, 3, 0, 0);
    func_0016898C(*(void**)(self + 0x47c), r);
    AnimArr* o = *(AnimArr**)(self + 0x47c);
    (*o)[0].m10 = 1.0f;
    r = func_002C11E8(buf, 1, 10, 0);
    func_0016898C(*(void**)(self + 0x480), r);
    o = *(AnimArr**)(self + 0x480);
    (*o)[0].m10 = 1.0f;
    ((Sub4C0*)(self + 0x4c0))->start(0x28);
    if (*(u16*)(self + 0x36) != 0) {
        func_00588C14(self, 0, 1);
    }
    func_00150A84(self, sead::SafeString("SE_BombL_MOVE_START"), 0);
}
