extern void func_0051E940(void* a, void* b);

struct Elem40 { unsigned int m0; void* m4; unsigned char rest[32]; };
struct Cont { int n; unsigned int m4; struct Elem40* d; };
struct Self { unsigned char pad[0xc]; struct Cont c; };

static inline struct Elem40* at(struct Cont* c, unsigned int i) {
    if (i < (unsigned int)c->n) return &c->d[i];
    return &c->d[0];
}

static inline struct Elem40* at2(struct Cont* c, unsigned int i) {
    if (i >= (unsigned int)c->n) return &c->d[0];
    return &c->d[i];
}

void func_00522B68(void* self, void* arg) {
    struct Self* s = (struct Self*)self;
    int i;
    for (i = 0; i < s->c.n; i++) {
        if (at(&s->c, (unsigned int)i)->m4 != 0)
            func_0051E940(at2(&s->c, (unsigned int)i)->m4, arg);
    }
}
