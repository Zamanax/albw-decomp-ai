typedef unsigned int u32;
typedef unsigned short u16;
typedef float f32;

struct Ctl { u16 a; u16 b; char p[4]; u32 c; };
struct Sub { char p0[0x1c]; u32 m1c; char p1[0x5c - 0x20]; Ctl ctl; };
struct Obj { char p0[0x1c]; u32 m1c; char p1[0xec - 0x20]; Ctl ec; char p2[4]; Sub* m_fc; };

void func_002317C0(void* control, f32 value);
void func_00474D7C(Obj* self) {
    Ctl* c = (Ctl*)((char*)&self->m1c + 0xd0);
    Obj * t1 = self;
    c->c = t1->m1c;
    u16 eight = 8;
    c->b = eight;
    u16 z0 = 0;
    c->a = z0;
    func_002317C0(c, 1.0f);
    Sub* s = t1->m_fc;
    func_002317C0((char*)s + 0x50, 1.0f);
    u32 m = s->m1c;
    u16 two = 2;
    Ctl* t0 = &s->ctl;
    t0->c = m;
    t0->b = two;
    t0->a = 0;
    func_002317C0(t0, 1.0f);
}
