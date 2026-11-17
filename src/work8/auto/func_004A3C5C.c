typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef void (*VFn)(void*);

struct Sub {
    void* obj;
    u32 key;
};

struct Entry {
    u8 active;
    u8 pad[3];
    struct Sub s;
    u8 rest[148];
};

struct Arg {
    u8 pad[8];
    u32 v;
};

struct Owner {
    struct Entry e[6];
    u8 pad[4];
    u32 count;
};

extern s32 func_0010FBAC(u32 key, u32 arg);

void func_004A3C5C(struct Owner* self, struct Arg* arg) {
    if (self->count == 0) {
        s32 i;
        for (i = 0; i < 6; i++) {
            struct Entry* e = &self->e[i];
            if (e->active) {
                struct Sub* p = &e->s;
                VFn fn = *(VFn*)((char*)p->obj + 8);
                fn(p);
                u32 k = p->key;
                if (func_0010FBAC(k, arg->v) == 0) {
                    e->active = 0;
                }
            }
        }
    }
}
