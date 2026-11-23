typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

struct HitE { char pad0[0x21]; s8 m21; char pad1; u8 m23; char pad2[0x30 - 0x24]; u16 m30; };

extern void* data_0070FB60;
extern u32 ro_00693840;
extern u32 ro_00693838;
extern s32 func_00588BE4(void* a);
extern s32 func_0058A1F4(void* a);
extern s32 func_0058A468(void* a);
extern u32 func_0055696C(void* p, u32 id);

f32 func_004F2E68(void* self, struct HitE* h) {
    if (func_00588BE4(self) == ro_00693840) {
        if (func_0058A1F4(self) != 0 && *((u8*)h + 0x21) == 8) return 100.0f;
    } else if (func_00588BE4(self) == ro_00693838) {
        s8 k = h->m21;
        if (k == 2 || h->m23 == 3) return 0.0f;
        if (k == 13) {
            if (func_0055696C(data_0070FB60, 12) >= 3) return 100.0f;
            return (f32)func_0058A468(self) / ((f32)h->m30 * 2.0f);
        }
    }
    return 1.0f;
}
