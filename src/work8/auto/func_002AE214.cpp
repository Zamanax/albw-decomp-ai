typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
struct M34E { char pad[0x508]; s16 m508; };
struct S2AD8A0 { char pad[0x34]; M34E* m34; char pad2[0xa4-0x38]; s8 bA4; };
extern "C" void func_002B193C(S2AD8A0*, int, float);
extern "C" void func_002AED24(S2AD8A0*);
extern "C" void func_002B0D7C(S2AD8A0*, int, int, int, float);
struct Kw { s32 k; void go(S2AD8A0* self, s32 x) { if (self->m34->m508 <= 0) { func_002B193C(self, x, 0.65f); return; } func_002AED24(self); s8 a = self->bA4; func_002B0D7C(self, x, 8, a, 0.25f); } };
void func_002AE214(S2AD8A0* self) {
    Kw w; w.k = 0xf;
    w.go(self, w.k);
}
