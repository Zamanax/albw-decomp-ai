struct Obj3248F8 {
    unsigned int first;
    float fl;
    unsigned int flags;
};

struct Input3248F8 {
    char pad[0x1c];
    float fl;
    unsigned short kind;
    char gap[6];
    unsigned int second;
};

extern "C" bool func_003248F8(Obj3248F8 *p, const Input3248F8 *q) {
    unsigned int flags = p->flags;
    unsigned int one = 1;
    unsigned int kind = q->kind & 31;
    if (flags & (one << kind)) return false;
    if (p->fl < q->fl) {
        p->fl = q->fl;
        p->first = q->second;
    }
    return true;
}
