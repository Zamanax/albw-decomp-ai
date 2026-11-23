typedef unsigned char u8;
typedef int s32;
typedef float f32;

typedef struct Ramp {
    f32 a;
    f32 b;
    s32 c;
    s32 d;
} Ramp;

extern f32 func_00111EA8(void* p);

void func_0040DA3C(void* self, int mode, int n)
{
    u8* o = (u8*)self;
    int st = o[0x9d];
    if (mode == 0) {
        if (st == 0) return;
        if (st != 1 && st != 2 && st != 3) return;
        f32 f = 1.0f - func_00111EA8(o + 0x74);
        s32 c = (s32)(f * (f32)n);
        if (c <= 0) c = 1;
        Ramp* r = (Ramp*)(o + 0x74);
        f32 b = 1.0f;
        f32 g = func_00111EA8(r);
        r->a = g;
        r->b = b;
        r->c = c;
        r->d = 0;
        o[0x9d] = 3;
        o[0x9f] = 1;
    } else {
        if (st != 0 && st != 1) {
            if (st == 2) return;
            if (st != 3) return;
        }
        f32 f = func_00111EA8(o + 0x74);
        s32 c = (s32)(f * (f32)n);
        if (c <= 0) c = 1;
        Ramp* r = (Ramp*)(o + 0x74);
        f32 b = 0.0f;
        f32 g = func_00111EA8(r);
        r->a = g;
        r->b = b;
        r->c = c;
        r->d = 0;
        o[0x9d] = 1;
        o[0x9f] = 0;
    }
}
