typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;

typedef struct Elem { u8 pad[0x18]; u8* base; } Elem;
typedef struct Holder { u8 pad[0xc]; Elem** arr; } Holder;
typedef struct Self { Holder* h; u8 pad[0x18c]; u32 idx; u32 k; u32 flags; } Self;

extern void* data_0070BB18;
extern void func_0016C004(void*, void*);
extern void func_0016C3C8(void*, void*);

void func_00351FC0(void* unused, Self* self) {
    Holder* h = self->h;
    u32 idx = self->idx;
    Elem* e = h->arr[idx];
    u32 k = self->k;
    u32 w = *(u32*)(e->base + 12 + 60 * k);
    u32 kind = (u8)self->flags;
    if ((s32)(w << 15) >= 0) {
        func_0016C004(data_0070BB18, self);
    }
    if (kind == 0 || kind == 1 || kind == 9) {
        func_0016C3C8(data_0070BB18, self);
    }
}
