extern unsigned int func_0056CE68(void*);

typedef unsigned int (*ObjFn4)(void*, unsigned int, unsigned int, unsigned int);

unsigned int func_005699DC(unsigned char* self, unsigned int a, unsigned int b, unsigned int c) {
    unsigned int r = func_0056CE68(*(void**)(self + 4));
    unsigned char* o = *(unsigned char**)(self + 8);
    if (o == 0) return r;
    unsigned int ra = a;
    unsigned int rb = b;
    unsigned int v;
    unsigned int rc = c;
    if (0 != o[4]) {
        v = (*(ObjFn4*)(0x40 + (char*)*(void**)o))(o, ra, rb, rc);
    } else {
        v = 0;
    }
    return v | r;
}
