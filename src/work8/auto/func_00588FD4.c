typedef unsigned int u32;
typedef float f32;

void func_00588FD4(char* self, u32* out) {
    char* p = *(char**)(self + 0x18);
    f32 s = *(f32*)(p + 0xac);
    *(f32*)out = s * 57.295776f;
    p = *(char**)(self + 0x18);
    out[1] = *(u32*)(p + 0x1a4);
    p = *(char**)(self + 0x18);
    out[2] = *(u32*)(p + 0x1a8);
    p = *(char**)(self + 0x18);
    out[3] = *(u32*)(p + 0xe4);
    p = *(char**)(self + 0x18);
    u32 a = *(u32*)(p + 0x198);
    u32 b = *(u32*)(p + 0x19c);
    *(out += 4) = a;
    out += 1;
    out[0] = b;
    out[1] = 0;
}
