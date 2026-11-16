struct Obj57D87C { unsigned char kind; unsigned char pad[3]; unsigned int f4; };
typedef int (*Fn1)(void*);
typedef int (*Fn2)(void*, void*);
extern Fn2 data_00716650[2];
int func_0057D87C(struct Obj57D87C* s, void* arg) {
    int r = 0;
    switch (s->kind) {
    case 1: {
        Fn2 f = data_00716650[0];
        if (f) r = f((void*)s->f4, arg);
        break;
    }
    case 2: {
        Fn1 f = (Fn1)s->f4;
        r = f(arg);
        break;
    }
    case 3: {
        Fn2 f = data_00716650[1];
        if (f) r = f((void*)s->f4, arg);
        break;
    }
    }
    return r;
}
