typedef int s32;
typedef unsigned int u32;
typedef float f32;
struct S800 { char pad[0x150]; f32 f150; };
struct Obj {
    char p0[0x3dc];
    f32 f3DC, f3E0, f3E4;
    char p3e8[0x908 - 0x3e8];
    u32 m908;
    u32 m90c;
};
extern "C" void func_004FC07C(void*, s32, s32, u32);
extern "C" void target(Obj* p) {
    p->m908 = 0;
    u32* q = &p->m90c;
    *q = 2;
    p->f3DC = 0.0f;
    p->f3E0 = 0.0f;
    p->f3E4 = 0.0f;
    ((S800*)((char*)p + 0x800))->f150 = 0.0f;
    func_004FC07C(p, 4, -1, 0);
}
