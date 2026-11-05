typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef signed char s8;

inline void* operator new(unsigned int, void* p) { return p; }

struct SafeStr {
    virtual ~SafeStr() {}
    virtual void assure() const;
    const char* text;
    SafeStr(const char* v) : text(v) {}
};

struct Obj;
typedef void (Obj::*Func)();
typedef void (Obj::*ExitFunc)(s32);

struct Elem {
    virtual void e0();
    virtual void e1();
    virtual void e2();
    const char* m4;
    u8 pad[0x24 - 0x8];
};

extern "C" void func_0010BEB4(void*, const SafeStr&);

struct Cnt {
    u32 v;
    Cnt(u32 x) : v(x) {}
};

struct StateMgr {
    Cnt count;
    s8 current;
    s8 next;
    u8 stateCount;
    u8 pad7;
    u32 elemNum;
    Elem* elems;
    void* timeline;
    Obj* owner;
    Func* enter;
    Func* execute;
    ExitFunc* exit;

    void callExit(s8 s);
    void callEnter();
    void setState(s32 s) {
        void* tl = timeline;
        s8 old = current;
        current = s;
        count = Cnt(0);
        next = old;
        if (tl) {
            u32 buf[2];
            void* pt = buf;
            Elem* e = elemAt(current);
            e->e2();
            func_0010BEB4(timeline, *new (pt) SafeStr(e->m4));
        }
    }
    Elem* elemAt(s32 i) {
        if ((u32)i >= elemNum) return elems;
        return &elems[i];
    }
};

void StateMgr::callExit(s8 s) {
    if (current != -1) {
        if (exit[current] != 0) (owner->*exit[current])(s);
    }
}

void StateMgr::callEnter() {
    s8 c = current;
    if (enter[c] != 0) (owner->*enter[c])();
}

struct Obj {
    void* vtbl;
    u8 pad1[0x6c - 4];
    StateMgr mgr;

    bool doIt(s8 s, s8 t);
};

typedef bool (*VFn)(Obj*, s8, s8);
bool Obj::doIt(s8 s, s8 t) {
    VFn f = ((VFn*)vtbl)[0x13c / 4];
    if (f(this, s, t)) {
        StateMgr* m = &mgr;
        m->callExit(s);
        m->setState(s);
        m->callEnter();
        return true;
    }
    return false;
}
