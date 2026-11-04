typedef unsigned char u8;
typedef unsigned int u32;

extern "C" const u8 ro_006A003B[];
extern "C" const u8 ro_006A0037[];
extern "C" const u8 ro_006A0045[];
extern "C" void* data_007142C8;
extern "C" void func_0051C63C(void* self, u32 v);

struct Self {
    char p0[0x9d2];
    u8 m9d2;
    u8 m9d3;
};

void func_00652F28(Self* self, u32 code) {
    if (self->m9d3 != 2) return;
    u32 v = 0;
    switch (self->m9d2) {
    case 0:
        v = ro_006A003B[code];
        break;
    case 1:
        v = ro_006A0037[code];
        break;
    case 2:
        v = ro_006A0045[code];
        break;
    default:
        break;
    }
    func_0051C63C(data_007142C8, v);
}
