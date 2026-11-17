typedef struct {
    unsigned int w0, w1, w2, w3, w4, w5, w6, w7, w8;
} Elem36;

static inline Elem36* at36(Elem36* b, unsigned int i) {
    if (i < 3u) return b + i;
    return b;
}

void func_003C33F0(Elem36* self) {
    int i;
    for (i = 0; i < 3; i++) {
        Elem36* d = at36(self, (unsigned int)i);
        Elem36* s = at36(self, (unsigned int)i);
        d->w1 = s->w2;
    }
}
