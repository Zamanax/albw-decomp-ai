typedef unsigned int u32;
typedef int s32;

typedef struct Ent {
    struct Ent* m0;
    char p1[0x18 - 4];
} Ent;

typedef struct Obj {
    char p0[0x54];
    s32 m54;
    char p1[4];
    Ent** m5c;
    Ent* m60;
    char p2[0x658 - 0x64];
    s32 m658;
} Obj;

void func_001E6CE8(void* p);

void func_005044B8(Obj* self) {
    s32 i;
    for (i = 0; i < self->m54; i++) {
        Ent* e = self->m5c[i];
        func_001E6CE8((char*)e + 0x18);
        e->m0 = self->m60;
        self->m60 = e;
    }
    self->m54 = 0;
    self->m658 = 0;
}
