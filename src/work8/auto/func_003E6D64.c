typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32;

typedef struct Item { u8 pad0[0x20]; s32 tag; u8 pad1[0xb0]; s32 flag; } Item;
typedef struct Owner { u8 pad0[8]; s32 count; s32 key; Item* items[8]; } Owner;

Item* func_003E6D64(Owner* o, s32 n) {
    s32 cnt = 0;
    for (s32 i = 0; i < o->count; i++) {
        if (o->items[i]->tag == o->key && o->items[i]->flag != 0) {
            if (cnt == n) return o->items[i];
            cnt++;
        }
    }
    return 0;
}
