typedef unsigned int u32; typedef int s32; typedef unsigned char u8;
struct Owner22 {};
typedef void(Owner22::*Method22)(u32);
extern const Method22 ro_006BB358[];
struct Group22 { u8 pad[0x90]; Owner22* objects[16]; };
static inline Owner22* at(Group22* g, s32 i) { if (i > 15) return 0; return g->objects[i]; }
void func_0041BCC8(Group22* p, u32 mask, u32 value) {
    Method22 m = ro_006BB358[11];
    for (s32 i = 0; i < 16; ++i, mask >>= 1) {
        if (!mask) break;
        if (mask & 1) {
            Owner22* o = at(p, i);
            if (o) (o->*m)(value);
        }
    }
}
