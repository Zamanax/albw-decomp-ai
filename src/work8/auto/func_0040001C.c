struct Pair { unsigned int lo; unsigned int hi; };

struct Src {
    unsigned char pad0[0x44];
    unsigned char f44[0x60];
    struct Pair pa4;
    unsigned char padac[0x14];
    unsigned int c0;
    unsigned char flags;
};

struct Dst {
    struct Pair p0;
    struct Pair p8;
    float m10;
    unsigned char m14;
    unsigned char m15;
    unsigned char m16;
    unsigned char m17;
};
void func_0040001C(struct Dst *dst, struct Src *src)
{
    struct Pair t = { src->c0, (unsigned int)src->f44 };
    dst->p0 = t;
    dst->p8 = src->pa4;
    dst->m10 = 1.0f;
    dst->m14 = src->flags & 1;
    dst->m15 = (src->flags & 2) >> 1;
    unsigned char z = 0;
    dst->m16 = (src->flags & 4) >> 2;
    dst->m17 = z;
}
