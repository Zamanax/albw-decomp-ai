extern void func_00419534(unsigned char* self);

void func_00419C7C(unsigned char* self)
{
    unsigned int i;

    func_00419534(self);
    *(unsigned char*)(self + 0x50) = 0;
    *(unsigned char*)(self + 0x51) = 0;
    *(unsigned char*)(self + 0x53) = 0;
    *(unsigned char*)(self + 0x54) = 0;
    *(unsigned char*)(self + 0x55) = 0;
    *(unsigned char*)(self + 0x52) = 0;
    *(unsigned int*)(self + 0x58) = 0;
    *(float*)(self + 0xf4) = 1.0f;
    *(unsigned char*)(self + 0xf8) = 0x7f;
    *(unsigned char*)(self + 0xf9) = 0;
    *(unsigned char*)(self + 0xfa) = 0;

    for (i = 0; i < 4; i++) {
        unsigned char* p = self + i * 36;
        unsigned char* e;
        p += 0x1800;
        e = p + 0x304;
        e[0x00] = 0;
        e[0x0c] = 0;
        e[0x0d] = 0x7f;
        e[0x0e] = 0x40;
        *(float*)(e + 0x18) = 1.0f;
        *(float*)(e + 0x1c) = 0.0f;
        *(float*)(e + 0x20) = 0.0f;
    }

    for (i = 0; i < 8; i++) {
        unsigned char* q = self + i * 832;
        *(unsigned int*)(q + 0x104) = 0;
        *(unsigned int*)(q + 0x134) = 0;
    }
}
