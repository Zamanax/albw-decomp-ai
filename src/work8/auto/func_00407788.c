typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;

typedef struct Obj40E8 {
    u32 a0;
    u32 a1;
    u32 a2;
    u32 a3;
    u32 b0;
    u32 arr[9];
    u16 h;
    u8 flag;
} Obj40E8;

void func_00407788(Obj40E8* o)
{
    o->a0 = 0;
    o->a1 = 0;
    o->a2 = 0;
    o->a3 = 0;
    o->h = 0;
    o->b0 = 0;
    Obj40E8 * t0 = o;
    t0->arr[0] = t0->flag = 0;
    u32 i = 1;
    u32 k = 1;
    do {
        u32* pa = &o->arr[i];
        i++;
        k += 2;
        u32* pb = &o->arr[i];
        *pa = 0;
        *pb = 0;
        i++;
    } while ((int)k < 9);
}
