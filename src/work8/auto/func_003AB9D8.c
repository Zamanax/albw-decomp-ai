typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;

typedef struct Elem340 { u16 flags; u8 pad[338]; } Elem340;
typedef struct ElemArr { Elem340* items; s32 count; } ElemArr;
typedef struct Owner { u8 pad[0x20]; ElemArr* arr; } Owner;
void func_003AB9D8(void* unused, Owner* o, s32 flag) {
    s32 i;
    s32 n = o->arr->count;
    for (i = 0; i < n; i++) {
        ElemArr* a = o->arr;
        Elem340* e = &a->items[i];
        if (e != 0) {
            if (flag == 0) e->flags = (u16)(e->flags & ~0x400);
            else e->flags = (u16)(e->flags | 0x400);
        }
    }
}
