extern void func_005FFDC0(void);
extern void* func_001150B0(void*, void*);
extern void* func_0041F7CC(void*);
extern void func_0041F7DC(void);
extern void* func_002FE918(void*);
extern void func_00403F18(void*, void*, void*, int);
extern void func_0026DEB0(void*, int);

void func_0012EC04(char* p, int flag) {
    func_005FFDC0();
    char* m = p + 0x1400 + 0x29c;
    if (flag) m += 0x40;
    void* r = func_001150B0(p + 0x6b4, m);
    void* a = func_0041F7CC(r);
    (*(void (**)(void*, void*, void*, int))(*(char**)(p + 0x20) + 0x20))(p + 0x20, a, p + 0x6b4, 0);
    func_0041F7DC();
    char* s = p + 0x1800;
    s += 0x24;
    void* o = func_002FE918(*(void**)s);
    void* b = func_0041F7CC(o);
    func_00403F18(p + 0x20, b, p + 0x6b4, 0);
    func_0041F7DC();
    func_0026DEB0(*(void**)(p + 0x1434), flag == 0);
    char* n = p + 0x1400 + 0x31c;
    if (flag) n += 0x40;
    void* r2 = func_001150B0(p + 0x6b4, n);
    void* a2 = func_0041F7CC(r2);
    (*(void (**)(void*, void*, void*, int))(*(char**)(p + 0x20) + 0x20))(p + 0x20, a2, p + 0x6b4, 0);
    func_0041F7DC();
    void* o2 = func_002FE918(*(void**)(s + 4));
    void* b2 = func_0041F7CC(o2);
    func_00403F18(p + 0x20, b2, p + 0x6b4, 0);
    func_0041F7DC();
}
