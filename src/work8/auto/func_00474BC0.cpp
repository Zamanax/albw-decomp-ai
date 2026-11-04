typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef float f32;

extern "C" void func_002317C0(void* control, f32 value);

struct Ctrl231 {
    s16 kind, index;
    u32 frame;
    void* owner;
    void init(void* p, s16 i, s16 k) { owner = p; index = i; kind = k; }
};

struct Sub474 {
    u8 pad0[0x1c];
    void* owner;
    u8 pad20[0x5c - 0x20];
    Ctrl231 ctrl;
};

struct Obj474 {
    u8 pad0[0xfc];
    Sub474* sub;
};

void func_00474BC0(Obj474* p) {
    Sub474* s = p->sub;
    func_002317C0((u8*)s + 0x50, 1.0f);
    s->ctrl.init(s->owner, 2, 0);
    func_002317C0(&s->ctrl, 1.0f);
}
