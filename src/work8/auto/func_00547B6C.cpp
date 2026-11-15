typedef unsigned int u32;
struct BitTable_00547B6C {
    u32 first;
    u32 count;
    u32* words;
    static u32 makeMask(u32 bit);
};
u32 BitTable_00547B6C::makeMask(u32 bit) { u32 one = 1; return one << bit; }
bool func_00547B6C(BitTable_00547B6C* t, u32 bit) {
    u32* p = t->words;
    if (t->count > t->first) p = p + t->first * 3;
    u32 word = p[bit >> 5];
    u32 m = BitTable_00547B6C::makeMask(bit & 31);
    return (m & word) != 0;
}
