extern void* func_001B6E04(void);
extern void* func_002608C8(void*, unsigned int, unsigned int, unsigned int, unsigned int);
extern char ro_006E3210[];
extern char ro_006E5C48[];

void* func_0037BAD4(void* self, unsigned int a, unsigned int b, unsigned int c, unsigned int fbits) {
    float f = *(float*)&fbits;
    char* o = (char*)func_001B6E04();
    *(char**)o = ro_006E3210;
    unsigned int zero = 0;
    *(unsigned int*)(o + 0x38) = zero;
    char* r = (char*)func_002608C8(o + 0x3c, a, b, c, *(unsigned int*)&f);
    char* vt2 = ro_006E5C48;
    *(char**)r = vt2 + 0x64;
    r -= 0x3c;
    *(char**)r = vt2;
    return r;
}
