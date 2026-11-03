// 0x58F214
struct Elem {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(void* a);
};
struct Obj {
    char pad[0x610];
    int count;
    int pad2;
    Elem** data;
};
struct Cls {
    void f(void* arg);
};
static inline Elem* at(Obj* o, int n, unsigned i) { if ((unsigned)n > i) return o->data[i]; return 0; }
void Cls::f(void* arg) {
    Obj* o = (Obj*)((char*)this - 0x320);
    int n = o->count;
    for (int i = 0; n > i; ++i) {
        Elem* p = at(o, n, i);
        p->v22(arg);
        n = o->count;
    }
}
