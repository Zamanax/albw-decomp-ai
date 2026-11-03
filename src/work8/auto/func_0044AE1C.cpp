/* func_0044AE1C - actor flag/param setup (matched, 43/43 words) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct BitFlag16 {
    u16 v;
    void change(u16 mask, bool on) { if (on) v |= mask; else v &= ~mask; }
    void set(u16 mask) { change(mask, true); }
};

struct Mgr  { u8 pad[0x5d]; u8 b5d; };
struct Child {
    u8 pad0[4];
    u32 val;             /* 0x04 */
    u8 pad1[0xe];
    BitFlag16 flags;     /* 0x16 */
};
struct Node { u8 pad[0x16]; BitFlag16 flags; };

struct Actor {
    u8 pad0[0x14];
    Child* child;        /* 0x14 */
    u8 pad18[0x1f0];
    u8 b208;             /* 0x208 */
    u8 pad209[3];
    u32 f20c;            /* 0x20c */
    Mgr* mgr;            /* 0x210 */
    u32 f214;            /* 0x214 */
    u32 f218;            /* 0x218 */
    u8 pad21c[0x14];
    Node* node;          /* 0x230 */
    u8 pad234[0x5e];
    u8 b292;             /* 0x292 */
    u8 b293;             /* 0x293 */
};

extern "C" {
extern u32 data_0070B728;
void func_004727B8(u32, u32);
void func_002C00A8(u32);
void func_0046A1D4(u32, u32);
u32 func_00584B94(u32, u32);
}

void func_0044AE1C(Actor* p) {
    p->b292 = 0;
    p->b293 = 0;
    if (p->mgr->b5d == 0) {
        func_004727B8(p->f20c, 1);
        func_002C00A8((u32)p->child);
        Child* c = p->child;
        u32& slot = c->val;
        u32 v = p->f218;
        slot = v;
        u32 b = slot;
        if (b) b = 1;
        BitFlag16* f = &c->flags;
        u16 x = f->v;
        if (b) x |= 0x40; else x &= ~0x40;
        f->v = x;
        if (func_00584B94(data_0070B728, 0x20a) != 0) {
            func_0046A1D4(p->f214, 1);
        }
        if (p->b208 != 0) {
            p->node->flags.set(0x40);
        }
    }
}
