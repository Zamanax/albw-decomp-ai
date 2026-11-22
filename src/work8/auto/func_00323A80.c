struct S323A80Arg { unsigned char kind; unsigned char pad[3]; void *val; };
struct S323A80 {
    char a[0x1d4];
    void *m1d4;
    char b[0xc];
    float m1e4;
    char c[1];
    unsigned char m1e9;
    char d[2];
    struct { char e[0x50]; unsigned char m50; } *m1ec;
};
void func_00532CC0(void *self, int flag, float f);
void func_00539418(struct S323A80 *self, void *val, float *v);
static float min1(float a, float b) { return a < b ? a : b; }

void func_00323A80(struct S323A80 *self, struct S323A80Arg *a) {
    unsigned char k = a->kind;
    float t = min1(self->m1e4 * 2.0f, 1.0f);
    if (k == 2) {
        void *val = a->val;
        float z = 0.0f;
        float v[4] = {z, z, z, t};
        func_00539418(self, val, v);
        return;
    }
    if (self->m1d4 == 0) return;
    {
        void *q = self->m1ec;
        if (self->m1ec->m50 != 2) return;
        func_00532CC0(q, k == 0, self->m1e9 == 3 ? t : 1.0f);
    }
}
