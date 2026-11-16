struct S {
    unsigned int m0;
    unsigned short m4;
    unsigned short m6;
    unsigned char m8;
    unsigned char m9;
    unsigned char m10;
    unsigned char m11;
    unsigned char m12;
    float m16;
    unsigned char m20;
    unsigned char m21;
    unsigned char m22;
    unsigned char m23;
    unsigned char m24;
    unsigned char m25;
};

void func_003CD388(struct S *s)
{
    unsigned int z = 0;
    unsigned char *q;
    float f = 0.0f;

    s->m0 = z;
    s->m4 = z;
    s->m6 = z;
    q = &s->m8;
    *q = 0xC;
    q = &s->m9;
    *q = 2;
    s->m10 = *q;
    s->m11 = z;
    s->m12 = z;
    s->m16 = f;
    s->m20 = z;
    s->m21 = z;
    s->m22 = z;
    s->m23 = z;
    s->m24 = z;
    s->m25 = z;
}
