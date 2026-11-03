typedef unsigned int u32;
typedef unsigned char u8;
struct Entry { char pad[0x1c]; u32 flags; char pad2[0x190 - 0x20]; };
struct G { char pad[0x10]; Entry entries[1]; };
struct S { char pad[0x70]; u8 index; };
struct C {
    char pad[0x18];
    u32 count;
    u32 pad1c;
    S** items;
    S* at(u32 i) { if (i < count) return items[i]; return 0; }
};
extern G* data_007124F0;
bool func_00522958(C* c) {
    if (c->count == 0) return false;
    S* s = c->at(c->count - 1);
    Entry* e = data_007124F0->entries;
    if (e[s->index].flags & 1) return true;
    return false;
}
