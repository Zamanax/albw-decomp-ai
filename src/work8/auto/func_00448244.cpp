typedef unsigned char u8; typedef unsigned int u32; typedef int s32;

struct Item {
    char pad[0xd]; u8 b0d; u8 b0e; char pad0f[0x6c - 0xf]; u8 b6c;
    bool isDone() const { return b0d == 3 && b0e == 3; }
};

#include "sead_container.h"


extern void* data_007142C8;
extern "C" u32 func_0058DA7C(void*);
extern "C" void func_0051AA20(void*);
extern "C" u32 func_0058DABC(void*);
extern "C" u32 func_00532C78(void*);
extern "C" void func_0066CC58(void*, s32);

struct Menu {
    char pad0[0x1ac]; PtrArray<Item> m1ac;
    char pad1b8[0x214 - 0x1b8]; Item* m214;
    char pad218[0x260 - 0x218]; float f260;
    char pad264[0x290 - 0x264]; u8 b290;
    void update();
};

void Menu::update()
{
    bool ok = true;
    for (s32 i = 0; i < 20; i++) {
        if (!m1ac.at(i)->isDone() && m1ac.at(i)->b6c) {
            ok = false;
            break;
        }
    }
    if (func_0058DA7C(data_007142C8)) func_0051AA20(data_007142C8);
    if (f260 <= 0.0f) {
        if (func_0058DABC(data_007142C8)) {
            if (!func_00532C78((char*)this + 0xf8)) {
                if (!(m214->b0d == 1 && m214->b0e == 1)) {
                    if (ok) {
                        if (b290) func_0066CC58((char*)this + 0x158, 2);
                        else func_0066CC58((char*)this + 0x158, 0);
                    }
                }
            }
        }
    }
}
