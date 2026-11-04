struct Sub286D { char pad[8]; float f8; float fC; float f10; float f14; char pad2[0x1c - 0x18]; unsigned char b1c; };
struct Mid286D { char pad[0x14]; Sub286D* m14; };
struct Pair286D { unsigned a; unsigned b; };
struct Inner286D { char p0[0x0c]; char p1[0x2c]; Mid286D* m438; Pair286D cnt; };
struct S286D00 { char pad[0x400]; Inner286D s; };
extern "C" void func_0065C454(void*, int);
void func_001CEF80(S286D00* self) {
    Sub286D* o = self->s.m438->m14;
    if (o->b1c != 0) return;
    float z = 0.0f;
    if (o->f10 >= z) {
        if (o->f8 == o->f14) goto doCall;
        return;
    } else {
        if (o->f8 <= z) {} else return;
    }
doCall:
    Pair286D p = self->s.cnt;
    if (p.b > p.a) {
        self->s.cnt.a = p.a + 1;
        return;
    }
    func_0065C454(self->s.p1, 2);
}
