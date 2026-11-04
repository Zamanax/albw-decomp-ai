typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

struct Ring112 {
    u32 m00;
    u32 m04;
    u32 m08;
    u32 m0c;
};

struct Obj {
    u8 pad0[0x14];
    Ring112 rings[5];

    Ring112* at(u32 i) {
        Ring112* p = rings;
        if (i < 5)
            p += i;
        return p;
    }
};

extern u32 data_00711F50;
s32 func_00587FCC(u32 mgr);
bool func_00537E04(u32 node, s32 id);

void func_0029678C(Obj* self)
{
    s32 sb = func_00587FCC(data_00711F50);
    if (sb == -1)
        return;
    for (s32 i = 0; i <= 2; i++) {
        if (self->at(i)->m08 == 0)
            continue;
        Ring112* e = self->at(i);
        u32 a = e->m04;
        u32 b = e->m0c;
        u32 r4 = a - b;
        Ring112* x = self->at(i);
        u32 r6 = (u32)x - x->m0c;
        while (r4 != r6) {
            u32 node = r4;
            if (func_00537E04(node, sb)) {
                u32* f = (u32*)(r4 + 0x38);
                *f |= 0x100;
            }
            r4 = *(u32*)(r4 + b + 4) - b;
        }
    }
}
