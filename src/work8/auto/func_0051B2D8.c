extern void func_0012C790(void *p);
extern void func_001B6B38(void *p);

void func_0051B2D8(char *self)
{
    unsigned char *p;
    unsigned char *q;
    if (*(unsigned short *)(self + 0x58) == 3) {
        p = *(unsigned char **)(self + 0x54);
        if (p != 0) {
            if (p[0xd] != 0 || p[0xe] != 0) {
                func_0012C790(p);
                func_001B6B38(*(void **)(self + 0x54));
                if (*(unsigned char **)(self + 0x54) == 0)
                    goto L74;
            }
            q = *(unsigned char **)(self + 0x50);
            if (q != 0)
                (*(void (**)(void *))(*(char **)q + 0x28))(q);
            *(void **)(self + 0x54) = 0;
            *(unsigned short *)(self + 0x58) = 0xffff;
        }
    }
L74:
    if (*(unsigned short *)(self + 0x74) == 2) {
        p = *(unsigned char **)(self + 0x70);
        if (p != 0 && (p[0xd] != 0 || p[0xe] != 0)) {
            func_0012C790(p);
            func_001B6B38(*(void **)(self + 0x70));
        }
    }
    {
        unsigned char *r = *(unsigned char **)(self + 0xf8);
        if (r != 0) {
            void *vt = *(void **)r;
            q = r;
            (*(void (**)(void *))((char *)vt + 0x34))(r);
            q[0xe] = 0;
            q[0xd] = 0;
        }
    }
}
