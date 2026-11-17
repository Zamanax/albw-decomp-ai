typedef unsigned int u32;
typedef struct { u32 a; u32 b; } Pair8;
typedef struct { char pad0[8]; char* tbl; } Owner8;

int func_0056AA40(Owner8* self, Pair8* out, u32 idx) {
    char* t = self->tbl;
    if (t == 0) return 0;
    char* q = 0;
    if (*(u32*)t > idx) q = t + *(u32*)(t + idx * 8 + 8);
    if (q == 0) return 0;
    *out = *(Pair8*)q;
    return 1;
}
