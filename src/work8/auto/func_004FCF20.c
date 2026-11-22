typedef unsigned int u32;
typedef unsigned char u8;

u32 func_004FCF20(u8 *self, u32 v)
{
    u32 *arr = (u32 *)(self + 0x8c);
    u8 *cnt = self + 0xab;
    u32 n;
    u32 i;
    u32 ret = 0;

    if (v != 0) {
        n = *cnt;
        if (n < 7) {
            ret = 1;
            for (i = 0; i < n; i++) {
                if (arr[i] == v) {
                    goto done;
                }
            }
            arr[n] = v;
            (*cnt)++;
        done:
            return ret;
        }
    }
    return 0;
}
