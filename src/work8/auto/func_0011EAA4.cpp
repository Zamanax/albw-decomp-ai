typedef unsigned int u32;
typedef int s32;
struct Ent16 { void* p; u32 a, b, c; };
struct Owner16 { u32 w0, w4, w8; Ent16* base; s32 k; };
void* f_0011EAA4(Owner16* o, s32 i) {
    if (o->k == -1) return 0;
    Ent16* e = &o->base[o->k];
    return (char*)e->p + 16 + i * 16;
}
