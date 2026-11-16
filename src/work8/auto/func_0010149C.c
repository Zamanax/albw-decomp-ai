typedef unsigned int u32;
typedef int s32;
struct RoObj { u32 a; u32 b; };
extern const struct RoObj ro_006A7FEC;
extern u32 data_0071613C;
extern u32 func_00103CBC(u32 a);
extern s32 func_00104868(u32* out, u32 name, u32 count, u32 flags);

u32 func_0010149C(void) {
    const struct RoObj* ro = &ro_006A7FEC;
    u32 b = ro->b;
    if (data_0071613C == 0) {
        u32 n = func_00103CBC(b);
        s32 r = func_00104868(&data_0071613C, b, n, 0);
        u32 s = (u32)r >> 31;
        if (s != 0) {
            return (u32)r;
        }
    }
    return 0;
}
