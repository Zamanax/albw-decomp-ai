struct Obj { char pad[0x4c]; unsigned char m4c; };
struct Cls { char pad[0x10]; struct Obj* m10; };

unsigned int func_0048A16C(struct Cls* self) {
    struct Obj* o = self->m10;
    if (!o) return (unsigned int)o;
    unsigned int r = 0;
    unsigned char f = o->m4c;
    unsigned int* rp = &r;
    if (f) {
        void (*fp)(struct Obj*, unsigned int*, struct Cls*) =
            *(void (**)(struct Obj*, unsigned int*, struct Cls*))((char*)(*(void**)o) + 0x48);
        fp(o, rp, self);
    }
    return r;
}
