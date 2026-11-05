typedef unsigned int u32;
typedef unsigned char u8;
extern void* data_0070B850;
extern void* data_007124F0;
extern void* data_00711F50;
extern "C" u32 func_00532C78(void*);
extern "C" void func_00166C00(void*, u32);
extern "C" void func_0045918C(void*);
extern "C" void func_00459388(void*);
extern "C" void func_00457510(void*);
extern "C" void func_0066D544(void*, u32);
extern "C" void func_00587F74(void*, void*, void*);


#include "sead_string.h"
namespace sead {

}

extern "C" void func_00457FC0(void* self) {
    void* global = data_0070B850;
    if (((u8*)global)[0xa4] == 0) {
        void* sub = *(void**)((u8*)self + 0x1c4);
        if (((u8*)sub)[0x8c] == 0 && ((u8*)sub)[0xa8] == 0) {
            if (func_00532C78((u8*)self + 0x134) == 0) {
                u32 i = *(u32*)((u8*)self + 0x230);
                u8* base = (u8*)self + 0x1e4;
                if (i < 3) base += i * 4;
                void* p = *(void**)base;
                if (func_00532C78((u8*)p + 0xec) == 0) {
                    *((u8*)self + 0x224) = 1;
                    func_00166C00(data_0070B850, 1);
                }
            }
        }
    }

    func_0045918C(self);

    void* tableOwner = data_007124F0;
    u32 index = *((u8*)self + 0x70);
    u8* table = (u8*)tableOwner + 0x10;
    u32 nineIndex = index + index * 8;
    u32 twentyFiveIndex = nineIndex + index * 16;
    u8* entry = table + twentyFiveIndex * 16;
    u32 checkAddr = (u32)entry + 0x10;
    if (*((u8*)self + 0x224) != 0 && (*(u32*)checkAddr & 1) != 0)
        return func_00459388(self);

    void* sub2 = *(void**)((u8*)self + 0x1c4);
    if (((u8*)sub2)[0x8c] != 0) {
        func_00457510(self);
        func_0066D544((u8*)self + 0x17c, 0x1c);
        const sead::SafeString& snd = sead::SafeString("SE_S_DECIDE");
        func_00587F74(data_00711F50, (void*)&snd, 0);
    }
}
