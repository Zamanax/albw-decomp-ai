extern unsigned int func_003D3800(unsigned int, unsigned int);
extern unsigned int func_003D48F4(unsigned int, unsigned int);
extern unsigned int func_003D4D38(unsigned int, unsigned int);
extern unsigned int func_003D4DFC(unsigned int, unsigned int, unsigned int, unsigned int, int);
extern unsigned int func_003D3904(unsigned int, unsigned int);

void func_0048BDDC(char* s)
{
    unsigned int r = func_003D3800(*(unsigned int*)(s + 0x15bc), (unsigned int)(s + 0x15c0));
    if (r != 0)
        *(unsigned int*)(s + 0x1634) = *(unsigned int*)(s + 0x1634) | 1u;
    else
        *(unsigned int*)(s + 0x1634) = *(unsigned int*)(s + 0x1634) & ~1u;
    if (func_003D48F4(*(unsigned int*)(s + 0x15d0), (unsigned int)(s + 0x15d4)) != 0)
        *(unsigned int*)(s + 0x1634) = *(unsigned int*)(s + 0x1634) | 2u;
    else
        *(unsigned int*)(s + 0x1634) = *(unsigned int*)(s + 0x1634) & ~2u;
    unsigned int* f = (unsigned int*)(s + 0x1634);
    unsigned int v = *(unsigned int*)(s + 0x15dc);
    if (v != 0 && func_003D4D38(v, (unsigned int)(s + 0x15e0)) != 0) {
        unsigned int t = *f;
        *f = t | 4u;
        func_003D4DFC(*(unsigned int*)(s + 0x15dc), (unsigned int)(s + 0x15e8), 1, (unsigned int)(s + 0x15e0), -1);
    } else
        *f = *f & ~4u;
    unsigned int w = *(unsigned int*)(s + 0x15f4);
    if (w != 0 && func_003D3904(w, (unsigned int)(s + 0x15f8)) != 0)
        *f = *f | 8u;
    else
        *f = *f & ~8u;
}
