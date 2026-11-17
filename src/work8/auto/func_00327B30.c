typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
extern void* data_0070FB60;
extern void func_004E74E8(void*, void*, u32, u32);

typedef struct { u32 x; u32 y; u32 z; } T3;
typedef struct { T3 v; u32 w; } T4;

void func_00327B30(void* self, u32 p1, u32 p2, u32 p3) {
    T4 t;
    T3* q = (T3*)((char*)self + 0x3d0);
    t.w = *(u32*)(*(char**)((char*)data_0070FB60 + 0x24));
    t.v = *q;
    func_004E74E8(&t, &t.w, 4, 0xffffffff);
}
