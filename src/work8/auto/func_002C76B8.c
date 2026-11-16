extern void func_006632F0(unsigned int *p, int n);

static inline char *adv(char *p, int n) { return p + n; }

void func_002C76B8(char *self)
{
    unsigned char a = *(unsigned char *)(self + 0x46a);
    char *p1 = self + 0x400;
    short t;
    unsigned int *q;
    unsigned char b;

    if (a) {
        func_006632F0((unsigned int *)adv(adv(self, 0x400), 0xc), 2);
        return;
    }
    t = *(short *)(p1 + 0x64);
    if (t > 0) {
        *(short *)(p1 + 0x64) = (short)(t - 1);
        return;
    }
    b = *(unsigned char *)(p1 + 0x68);
    q = (unsigned int *)(self + 0x438);
    if (b) {
        *q = *q + 0xfc000000u;
        *(float *)(self + 0x3d0) -= *(float *)(p1 + 0x34) * *(float *)(p1 + 0x5c);
        *(float *)(self + 0x3d8) -= *(float *)(p1 + 0x30) * *(float *)(p1 + 0x5c);
    } else {
        *q = *q + 0x4000000u;
        *(float *)(self + 0x3d0) += *(float *)(p1 + 0x34) * *(float *)(p1 + 0x5c);
        *(float *)(self + 0x3d8) += *(float *)(p1 + 0x30) * *(float *)(p1 + 0x5c);
    }
}
