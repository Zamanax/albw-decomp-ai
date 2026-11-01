typedef unsigned int u32;
struct BitArr_52A07C {
    char pad[0x1c];
    u32 mWords[8];
    static u32 makeMask(u32 bit);
    bool isOn(u32 i) const { const u32* p = mWords; u32 word = p[i >> 5]; u32 m = makeMask(i & 31); return (m & word) != 0; }
};
u32 BitArr_52A07C::makeMask(u32 bit) { u32 one = 1; return one << bit; }
struct Owner_52A07C { char pad[0x10]; BitArr_52A07C* p; bool isOn(u32 i) const; };
bool Owner_52A07C::isOn(u32 i) const { return p->isOn(i); }
