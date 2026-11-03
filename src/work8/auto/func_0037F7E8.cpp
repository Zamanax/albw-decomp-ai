typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

struct Vec3 { f32 x, y, z; };
extern Vec3 data_007A9260;
extern "C" Vec3* func_00520FC0(void*);
extern "C" void func_00115C70(Vec3*, const Vec3&, const Vec3&);
extern "C" s32 func_0068C690(const Vec3&);
extern "C" void func_0051D37C(s32*, u32, u32);
extern "C" void func_004FC07C(void*, u32, u32, u32);

static inline void copy38(Vec3* d,const Vec3& s){*d=s;}
extern "C" void func_0037F7E8(char* self) {
    Vec3 tmp;Vec3* tp=&tmp;copy38(tp,data_007A9260);
    Vec3* p = func_00520FC0(self);
    func_00115C70(tp, *p, *(Vec3*)(self + 0x3d0));
    s32 L = func_0068C690(tmp) - *(s32*)(self + 0x3e8);
    func_0051D37C(&L, 0xe0000000u, 0x20000000u);
    *(s32*)(self + 0xad8) = L;
    *(u8*)(self + 0xb2c) = 0;
    *(f32*)(self + 0x3dc) = 0.0f;
    *(f32*)(self + 0x3e4) = 0.0f;
    func_004FC07C(self, 5, 0xffffffffu, 0);
}
