#include "albw_types.h"

u32* func_00584CA8(void* p, s32 i, s32 j);
void func_004CF5DC(void* p, s32 i, s32 j, const u32* key);

struct Sub {
    void* m0;
    char pad[0x5c - 4];
    s32 m5c;
};

struct Cls {
    char pad[0x530];
    struct Sub sub;
};

void func_002C43B8(struct Cls* self) {
    u8 c = 0xff;
    s32 i = self->sub.m5c;
    u32 key = *func_00584CA8(self->sub.m0, i, 0);
    u8* kb = (u8*)&key;
    kb[3] = c;
    struct Sub* q = &self->sub;
    func_004CF5DC(q->m0, q->m5c, 0, &key);
}
