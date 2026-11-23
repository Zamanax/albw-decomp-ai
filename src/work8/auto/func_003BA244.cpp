typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern "C" s32 func_00542F3C(void* a);
extern "C" void* func_0058A7D4(void* a);
extern "C" u32 func_00111A64(void* self);
extern "C" s32 func_00543170(void* a);
struct Sub { u8 pad[9]; s8 m9; };
struct Act { u8 pad[0x8bc]; Sub* m8bc; };
struct Obj {
    u8 pad0[0x48];
    Act* m48;
    s32 m4c;
    f32 m50;
    void func_003BA244();
};

static f32 scaled(void* r, f32 max) { return (f32)func_00111A64(r) * (1.0f / 4294967296.0f) * max; }

void Obj::func_003BA244() {
    if (func_00542F3C(m48) != 0 || m48->m8bc->m9 > 0) {
        m50 = scaled(func_0058A7D4(m48), 1.8499999f) + 2.15f;
        if (func_00543170(m48) != 0) {
            m50 *= 0.5f;
        }
    } else {
        m50 = scaled(func_0058A7D4(m48), 2.0f) + 2.0f;
        if (func_00543170(m48) != 0) {
            m50 *= 0.5f;
        }
    }
}
