typedef unsigned int u32;
extern u32 data_0070B800;
extern void func_0012DEC8(u32 a, u32 b, u32 c);
extern void func_004A1520(void* p);
extern char ro_006E0690[];

void func_0031C00C(char* self) {
    char* vt = ro_006E0690;
    *(char**)self = vt;
    char* o = *(char**)(self + 0x20);
    *(char**)(self + 0x10) = vt + 0x18;
    u32 flag = 0;
    if (o != 0) {
        if (*(u32*)(o + 0x68) & 0x18) flag = 1;
    }
    func_0012DEC8(data_0070B800, *(u32*)(self + 0x2c), flag);
    func_004A1520(self);
}
