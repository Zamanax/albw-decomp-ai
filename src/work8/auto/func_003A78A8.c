typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef struct { char pad[0x70]; void* v; } Inner70;
typedef struct { f32 x, y, z; } V3;
typedef struct { char pad[0x118]; f32 x; f32 y; } Evt;
typedef struct { char pad[0xc8]; Evt* evt; } EvMgr;
typedef struct { char pad0[0x2c]; Inner70* a; char pad1[4]; V3* b; } Self;
extern EvMgr* data_0070B728;
extern u32 func_002FD11C(void* p, u32 f);

u32 func_003A78A8(Self* self) {
    if (self->a->v == 0 || func_002FD11C(self->a->v, 0) == 0) return 0;
    f32* p = &data_0070B728->evt->x;
    f32 sum = p[0] * p[0] + p[1] * p[1];
    s32 bits = *(s32*)&sum;
    if (bits <= 0x3c23d70a) {
        V3* b = self->b;
        b->x = 0.0f;
        b->z = 0.0f;
    }
    return 1;
}
