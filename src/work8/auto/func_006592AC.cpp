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

struct Owner;
typedef void (Owner::*Func)();
typedef void (Owner::*ExitFunc)(s32);

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
    Owner* owner;
    Func* enter;
    Func* execute;
    ExitFunc* exit;

    void callExit(s8 s);
    void callEnter();
    void setState(s32 s) {
        void* tl = timeline;
        s8 old = current;
        current = s;
        Cnt t3 = Cnt(0);
        count = (t3);
        next = old;
        if (tl) {
            s32 buf[2];
            void* pt = buf;
            Elem * t6 = elemAt(current);
            Elem * t5 = t6;
            Elem * t4 = t5;
            Elem * t1 = t4;
            Elem* e = t1;
            Elem * t2 = e;
            t2->e2();
            Elem * t0 = t2;
            func_0010BEB4(timeline, *new (pt) SafeStr(t0->m4));
        }
    }
    Elem* elemAt(u32 i) {
        if ((s32)i >= elemNum) return elems;
        return &elems[i];
    }
    bool requestState(s8 s);
};

void StateMgr::callExit(s8 s) {
    if (current != -1) {
        if (exit[current] != 0) (owner->*exit[current])(s);
    }
}

void StateMgr::callEnter() {
    if (0 != enter[current]) (owner->*enter[current])();
}

bool StateMgr::requestState(s8 s) {
    if (s == current) return false;
    callExit(s);
    setState(s);
    callEnter();
    return true;
}
