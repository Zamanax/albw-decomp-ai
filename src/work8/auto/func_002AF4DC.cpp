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
extern "C" float func_002AED24(S2AD8A0*, float);
extern "C" void func_002B0D7C(S2AD8A0*, int, int, int, float);
// func_002AF4DC: calls func_002AED24(self, f) which is a leaf that writes only self->bA4 and
// leaves s0 untouched, so the float argument is returned unchanged in s0 (declared as returning it).
void func_002AF4DC(S2AD8A0* self) {
    float f = 0.0f;
    if (self->m34->m508 <= 0) { func_002B193C(self, 0xe, f); return; }
    f = func_002AED24(self, f);
    s8 a = self->bA4;
    func_002B0D7C(self, 0xe, 8, a, f);
}
