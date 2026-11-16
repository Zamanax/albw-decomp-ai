typedef unsigned char u8;
typedef unsigned int u32;
struct Inner {
    char p0[0x73c];
    u32 a73c;
    u32 a740;
    char p1[0x7fc - 0x744];
    u8 b7fc;
    char p2[0x853 - 0x7fd];
    u8 b853;
};
struct Outer {
    char p0[0x34];
    struct Inner* in34;
    char p1[0xa4 - 0x38];
    u8 a4;
};

void func_002AED24(struct Outer* p) {
    struct Inner* in = p->in34;
    if (in->b853 != 0) {
        p->a4 = 0;
    } else if (in->b7fc == 5) {
        p->a4 = 0;
    } else {
        p->a4 = in->a73c < in->a740 ? 1 : 0;
    }
}
