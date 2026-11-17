typedef unsigned int u32;
typedef int s32;

void func_003E49E4(u32* dst, u32* base, s32 stride, u32* tbl)
{
    s32 k;
    for (k = 4; k > 0; k--) {
        u32* p = base + tbl[k];
        u32* q = p + stride;
        *dst++ = p[0];
        *dst++ = p[stride];
        *dst++ = p[1];
        p = p + 2 * stride;
        *dst++ = q[1];
        u32* r = p + stride;
        *dst++ = p[0];
        *dst++ = p[stride];
        *dst++ = p[1];
        *dst++ = r[1];
    }
}
