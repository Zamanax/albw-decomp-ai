typedef unsigned char u8; typedef int s32; typedef float f32;
struct Obj { u8 pad0[0x48]; f32 value; u8 pad1[0x516 - 0x4c]; u8 flag; };
extern "C" void func_006657B4(void*, s32);
extern "C" void func_003327FC(Obj* self) {
    if (!self->flag) {
        if ((s32)self->value == 1 || (s32)self->value == 3)
            func_006657B4((u8*)self + 0x4c0, 5);
    }
}
