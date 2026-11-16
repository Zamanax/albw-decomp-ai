typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

typedef struct Inner { u8 pad[0x508]; s16 state; } Inner;
typedef struct Obj { u8 pad[0x34]; Inner* child; u16 flags; } Obj;

extern void func_002B1644(Obj* p, u32 mode, u32 n);

void func_002AED7C(Obj* p, u32 n) {
    func_002B1644(p, 0x14, (u8)n);
    if (0 == n) {
        Obj * t0 = p;
        Inner* c = t0->child;
        if (c->state <= 0) {
            t0->flags = t0->flags | 1;
        }
    }
}
