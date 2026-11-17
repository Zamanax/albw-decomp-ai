// One translation unit: 0x412BB4, 0x412C68, 0x412F58 (address order = source order).
// The two function-local statics share the TU's guard area: 0x412F58's guard (0x7164A0) is
// addressed from the first guard (data_0071649C, 0x412BB4's) as `[r0, #4]`, which only happens
// when both functions are compiled in one file. Compiled alone, 0x412F58 loads its own guard (OP=2).
typedef unsigned char u8;
typedef unsigned int u32;

struct Obj {
    Obj();     // ctor func_00412FD4
    ~Obj();    // dtor func_006766F4 (registered with atexit; dso func_00100000)
    u8 p0[0x18e];
};

Obj* func_00412BB4() {
    static Obj obj;
    return &obj;
}

struct Node412 { Node412* next; };
struct Queue412 { u8 pad[0x16c]; Node412* head; Node412* tail; u32 count; };
u32 func_00412C68(Queue412* p, Node412* n) {
    if (p->tail == 0) p->head = n; else p->tail->next = n;
    p->tail = n;
    n->next = 0;
    return p->count;
}

Obj* func_00412F58() {
    static Obj obj;
    return &obj;
}
