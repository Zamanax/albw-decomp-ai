typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

extern char ro_006F5988[];
extern u32 func_00691884(void* a, void* b);

typedef u32 (*GetFn)(void*);
typedef void (*ActFn)(void*);

void func_004B0730(char* self, u32 p1, char* p2, u32 p3) {
    char** slot = (char**)(self + 0x1418);
    if (p1 < 0x10) slot += p1;
    char* obj = *slot;
    if (obj == 0) return;
    char* r5 = (char*)(((GetFn)(*(void***)obj)[3])(obj));
    ((ActFn)(*(void***)p2)[2])(p2);
    char* a = *(char**)(r5 + 0x20);
    u32 b = *(u32*)(p2 + 4);
    if (a == 0) return;
    u32 s0[2];
    u32 s1[2];
    s0[0] = (u32)ro_006F5988;
    s0[1] = b;
    char* head = *(char**)(r5 + 0x20) + 0x44;
    u32 base = *(u32*)(head + 0xc);
    u32 cur = *(u32*)(head + 4) - base;
    u32 end = (u32)head - base;
    while (cur != end) {
        u32 v = *(u32*)(*(u32*)(cur + 8) + 4);
        s1[0] = (u32)ro_006F5988;
        s1[1] = v;
        if (func_00691884(s0, s1) != 0) {
            u32* pp = (u32*)(cur + 0x20);
            char* c = (char*)pp[0];
            if (c != 0) {
                if (pp[1] == *(u32*)(c + 0xc)) {
                    if (*(s32*)(c + 4) > 0) *(u8*)(c + 0x280) = 1;
                }
            }
            u32* gp = (u32*)(cur + 0x3c);
            u32 g = *gp;
            *gp = (g & 0xfffffffbu) | 8u;
        }
        cur = *(u32*)(cur + base + 4) - base;
    }
}
