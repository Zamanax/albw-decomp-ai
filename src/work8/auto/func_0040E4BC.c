typedef unsigned int u32;
typedef unsigned short u16;
typedef int s32;
void func_0040E4BC(void* self, u32 p1, u32 p2, u32 p3) {
    s32 v = (s32)(p1 + 1);
    v = v * v;
    *(u16*)((char*)self + 0x14) = (u16)(v / 4);
}
