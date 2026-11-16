extern void* data_0070FB60;
extern unsigned int func_0055696C(void* p, unsigned int id);
extern unsigned int func_00521080(void* a, void* b);
extern float func_00528734(void* a, void* b, signed char c);

union f2i { float f; int i; };
struct Sub { char pad[0x15c]; float f; };

unsigned int func_001A71A8(char* self, char* q)
{
    char* m = self + 0x900;
    void* it = *(void**)(q + 0x34);
    if (it != 0 && *(unsigned short*)((char*)it + 0xa) == 4) {
        union f2i u;
        if (func_0055696C(data_0070FB60, 1) < 3) return 0;
        u.f = func_00528734(self, q + 0x10, *(signed char*)(m + 0x37));
        if (u.i >= 0x3e800000) {
            ((struct Sub*)(self + 0x800))->f = u.f;
            return 1;
        }
    } else {
        if (*(unsigned char*)(m + 0x37) == 0) return 1;
        if (func_00521080(self, q + 0x28) == 0) return 1;
    }
    *(unsigned char*)(self + 0x938) = 1;
    char* p = *(char**)(self + 0x8e4);
    *(unsigned char*)(p + 0x61) = 0;
    return 1;
}
