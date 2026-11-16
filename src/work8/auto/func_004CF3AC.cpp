typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

struct Elem {
    char pad[0x9d];
    u8 flag;
};

struct Arr {
    s32 n;
    s32 cap;
    Elem** p;
    Elem* at(s32 i) const {
        if ((u32)i < (u32)n)
            return p[i];
        return 0;
    }
};

struct Holder {
    char pad0[0x5c];
    Arr a;
    Arr b;
};

void func_004CF3AC(Holder* h, u8 v, s32 idx)
{
    if (idx >= 0) {
        h->a.at(idx)->flag = v;
        if (h->b.n != 0)
            h->b.at(idx)->flag = v;
        return;
    }
    for (s32 i = 0; i < h->a.n; i++)
        h->a.at(i)->flag = v;
    for (s32 i = 0; i < h->b.n; i++)
        h->b.at(i)->flag = v;
}
