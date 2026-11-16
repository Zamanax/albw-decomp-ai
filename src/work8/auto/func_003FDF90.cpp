#include "albw_types.h"

struct Node003FDF90 { Node003FDF90* next; };
struct Head003FDF90 { u32 unk0; Node003FDF90* next; };

static bool nameMatch003FDF90(const signed char* a, const signed char* b) {
    for (s32 i = 0; i < 0x18; i++) {
        if (a[i] != b[i]) return false;
        if (a[i] == 0) return true;
    }
    return true;
}

void* func_003FDF90(void* head, const void* key) {
    Node003FDF90* end = (Node003FDF90*)((u8*)head + 4);
    for (Node003FDF90* p = ((Head003FDF90*)head)->next; p != end; p = p->next) {
        const signed char* a = (const signed char*)p + 0x14;
        if (nameMatch003FDF90(a, (const signed char*)key)) return (u8*)p - 4;
    }
    return 0;
}
