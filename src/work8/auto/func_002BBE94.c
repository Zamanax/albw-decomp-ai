typedef struct Pair { unsigned int cur; unsigned int max; } Pair;
typedef struct Sub400 { char p[0xf8]; float f; } Sub400;
typedef struct Self {
    char p0[0x400];
    Sub400 s400;
    char p1[0x59c - 0x4fc];
    unsigned int f59c;
    char p2[0x900 - 0x5a0];
    Pair r;
} Self;
extern void func_004F87F8(void* self, int a);
extern void func_002BB5A0(void* self);

void func_002BBE94(Self* self) {
    Pair c = self->r;
    if (c.cur < c.max) {
        unsigned int t1 = c.cur;
        unsigned int n = 1 + t1;
        self->r.cur = n;
        if (n != 0) {
            Self * t2 = self;
            t2->f59c |= 0x30;
            func_004F87F8(self, 0);
        }
    }
    Pair d = self->r;
    Pair* t0 = &d;
    float f = 0.1f * (float)t0->cur;
    if (t0->cur >= t0->max || *(int*)&f > 0x3f800000) {
        f = 1.0f;
    }
    self->s400.f = f;
    func_002BB5A0(self);
}
