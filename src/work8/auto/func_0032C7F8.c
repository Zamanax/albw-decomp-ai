struct Obj { unsigned int w0; unsigned char pad4[0x34 - 4]; unsigned char m34; unsigned char pad35[0xa1 - 0x35]; unsigned char ma1; };
extern void func_0036E490(void*, int, unsigned int);
void func_0032C7F8(struct Obj* o) {
    struct Obj * t3 = o;
    unsigned char* p = &o->m34;
    unsigned int t2 = t3->w0;
    unsigned int t1 = t2;
    unsigned int t0 = t1;
    unsigned int v = t0;
    switch (*p) {
    case 5:
    case 6:
        p[0x6d] = 1;
        func_0036E490(p, 7, v);
        break;
    case 9:
    case 10:
    case 11:
        p[0x6d] = 1;
        func_0036E490(p, 11, v);
        break;
    default:
        break;
    }
}
