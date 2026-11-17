struct Sub { unsigned char pad[0xd]; unsigned char a; unsigned char b; };
struct Owner { unsigned char pad[0xf4]; struct Sub* child; };
extern void func_0012C790(struct Sub*);
extern void func_001B6B38(struct Sub*);

void func_00519B4C(struct Owner* o) {
    struct Sub* c = o->child;
    unsigned int f = (c->a == 0 && c->b == 0) ? 1 : 0;
    unsigned int t = f ^ 1;
    if (t == 0) return;
    func_0012C790(c);
    func_001B6B38(o->child);
}
