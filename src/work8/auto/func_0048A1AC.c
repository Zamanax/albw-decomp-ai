extern void func_00489F74(void*, unsigned int*, void*, unsigned int, unsigned int);

struct Obj48A1 { char pad[0x10]; void* child; };

unsigned int func_0048A1AC(struct Obj48A1* p, unsigned int a, unsigned int b) {
    unsigned int out;
    if (p->child) {
        out = 0;
        func_00489F74(p->child, &out, p, a, b);
        return out;
    }
    return 0;
}
