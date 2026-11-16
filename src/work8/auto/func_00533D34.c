typedef unsigned int u32;
typedef int s32;
typedef short s16;

struct Tail { char pad[0x50]; u32 m50; };
struct Mid { char pad[8]; struct Tail* t; };
struct Self { char pad0[0x54]; s16 m54; s16 m56; char pad1[0x5DC]; struct Mid* m634; };
struct Other { char pad[0x50]; u32 m50; };

extern u32 data_0070BB18;
extern void func_00522C70(u32, s32);
extern void func_00522D28(u32, s32);

void func_00533D34(struct Self* self, struct Other* other) {
    struct Self* s = self;
    struct Other* o = other;
    s32 idx = (s16)s->m56;
    if (idx < 0) idx = s->m54;
    struct Mid* mid = s->m634;
    struct Tail * t0 = mid->t;
    if (o->m50 == t0->m50) func_00522D28(data_0070BB18, idx);
    else func_00522C70(data_0070BB18, idx);
}
