typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef unsigned long long u64;

struct Vec3 { f32 x, y, z; };
extern Vec3 data_007A9260;
extern u32 data_0070ACC0;
extern "C" Vec3* func_00520FC0(void*);
extern "C" void func_00115C70(Vec3*, const Vec3&, const Vec3&);
extern "C" s32 func_004904CC(f32, f32);
extern "C" void func_0051D37C(s32*, u32, u32);
extern "C" void func_004FC07C(void*, u32, u32, u32);

static inline void copy38(Vec3* d,const Vec3& s){*d=s;}
extern "C" void func_001299C8(char* self) {
    Vec3 tmp;Vec3* tp=&tmp;copy38(tp,data_007A9260);
    Vec3* p = func_00520FC0(self);
    func_00115C70(tp, *p, *(Vec3*)(self + 0x3d0));
    s32 L = func_004904CC(tmp.x, tmp.z) - *(s32*)(self + 0x3e8);
    u32 k = data_0070ACC0;
    func_0051D37C(&L, 0u - k, k);
    *(s32*)(self + 0x930) = L;
    *(f32*)(self + 0x3dc) = 0.0f;
    *(f32*)(self + 0x3e4) = 0.0f;
    func_004FC07C(self, 3, 0xffffffffu, 0);
}
