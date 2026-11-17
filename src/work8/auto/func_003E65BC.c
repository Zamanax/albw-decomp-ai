typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef struct { s32 max; s32 cur; } Counter;

s32 func_003E65BC(Counter* c, s32 d) {
    if (d != 0) {
        s32 v = c->cur + d;
        s64 w = (u32)v;
        if (w > (s64)(u32)c->max) v = c->max;
        else if (w < 0) v = 0;
        c->cur = v;
    }
    return c->cur;
}
