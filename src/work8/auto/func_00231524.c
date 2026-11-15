typedef unsigned int u32;
typedef unsigned char u8;
typedef short s16;

typedef struct Target { u8 _p0[0x10]; u32 f10; } Target;
typedef struct Elem {
    u8 _p0[0x10];
    Target* p10;
    u32 f14;
    u8 _p1[8];
    u32 f20;
    u8 _p2[0x38 - 0x24];
} Elem;
typedef struct Table { u8 _p0[8]; u32 count; Elem* data; } Table;
typedef struct Owner { u8 _p0[2]; s16 idx; u8 _p1[4]; Table* tbl; } Owner;

extern void func_001672F8(void* t, float a, float b);

static inline Elem* elemAt(Table* t, u32 i) {
    if (i < t->count) return &t->data[i];
    return &t->data[0];
}

void func_00231524(Owner* p) {
    if (p->tbl != 0) {
        if (p->idx < 0) return;
        func_001672F8(p->tbl, 0.0f, 0.0f);
        Table* t = p->tbl;
        Elem* e1 = elemAt(t, (u32)p->idx);
        u32 v = e1->f20;
        Elem* e2 = elemAt(t, (u32)p->idx);
        e2->f14 = v;
        e2->p10->f10 = v;
    }
}
