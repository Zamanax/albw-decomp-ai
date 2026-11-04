typedef unsigned int u32;
typedef int s32;
typedef float f32;
struct Elem53F4 { char pad[0x10]; f32 v; };
struct Node53F4 {
    char pad0[0xc];
    u32 n;
    char pad1[4];
    Elem53F4* d;
    Elem53F4& at(u32 i) { if (i < n) return d[i]; return d[0]; }
};
extern "C" void func_001C52B0(void*, int, int);
extern "C" void func_001C51C8(void*, int, int);
extern "C" void func_00168E9C(void*, u32, int);
extern "C" void f_001C53F4(void* self) {
    func_001C52B0(self, 2, 0);
    func_001C51C8(self, 1, 0);
    Node53F4* a = *(Node53F4**)((char*)self + 0x7b8);
    a->at(0).v = 0.0f;
    func_00168E9C(*(void**)((char*)self + 0x7b8), *(u32*)((char*)self + 0x7b0), 0);
}
