typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

struct P561F74 { u8 m0; u8 m1; u8 m2; u8 pad; void* m4; };

u32* func_00562280(void* a, u32* b, s32 c);

u32* func_00561F74(struct P561F74* p, u32* out, s32 flag)
{
    u32 t = 0;
    if (p->m0 != 0) {
        if (p->m1 == 0) t = (p->m2 == 0) ? 2 : 1;
        else if (p->m1 == 1) t = (p->m2 == 1) ? 2 : 1;
        else t = 1;
    }
    out[0] = t;
    out[1] = 0x000F0040;
    out += 2;
    if (flag != 0)
        return func_00562280((char*)p->m4 + 0x7c, out, 1);
    return out;
}
