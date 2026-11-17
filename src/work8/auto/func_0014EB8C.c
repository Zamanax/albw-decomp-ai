extern void func_004EDEA0(void*, unsigned int);
extern void func_00435BE8(void*, void*);
extern void func_004A8BFC(void*, void*, unsigned int);
extern void* data_00709D28;
struct Par { unsigned short a4; float a5; unsigned short a6; };

int func_0014EB8C(char* self, unsigned int a1, void* a2, unsigned int a3, struct Par p) {
    unsigned char* q = (unsigned char*)self;
    *(unsigned int*)(q + 0x10) = a1;
    func_004EDEA0(self, a3);
    *(float*)(q + 0x1c) = p.a5;
    *(unsigned short*)(q + 0x32) = p.a6;
    if (a2 == 0) { *(unsigned short*)(q + 0x18) = p.a4; return 0; }
    *(unsigned short*)(q + 0x18) = p.a4;
    func_00435BE8(q + 0x20, a2);
    func_004A8BFC(data_00709D28, self, *(unsigned short*)((unsigned char*)a2 + 4) & 0xff);
    return 1;
}
