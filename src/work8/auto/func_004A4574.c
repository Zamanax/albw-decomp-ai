extern unsigned long long func_00110710(unsigned int a, unsigned int b);

void func_004A4574(char* p, unsigned int x)
{
    char* a = *(char**)(p + 0x1c);
    unsigned int n = *(unsigned int*)(a + 8);
    char* e = *(char**)(a + 0xc);
    float f = *(float*)((n > 1 ? e + 0x38 : e) + 0x20);
    unsigned int r = (unsigned int)(func_00110710(x, (unsigned int)f) >> 32);
    float g = (float)r;
    char* t = n > 1 ? e + 0x38 : e;
    *(float*)(t + 0x14) = g;
    *(float*)(*(char**)(t + 0x10) + 0x10) = g;
}
