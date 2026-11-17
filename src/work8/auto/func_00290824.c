extern char* data_00709DF8;
extern void func_001DE378(void* self, void* pos, unsigned int w);
extern void func_002D55D0(void* st, int id);

struct F3 { float x; float y; float z; };

int func_00290824(char* self, float s0) {
    char* g = data_00709DF8;
    char* q = g + 0x18;
    if (!(*(unsigned char*)q == 0x16 && *(unsigned int*)(q + 4) == 1)) return 0;
    char* m = *(char**)(self + 0x10);
    if (*(unsigned int*)(m + 0x5b0) != 0x3f800000u) return 0;
    if (*(unsigned short*)(self + 0x42) == 0x3f) return 0;
    struct F3* pv = (struct F3*)(m + 0x3d0);
    struct F3 p = *pv;
    p.y = s0;
    func_001DE378(*(void**)(self + 0x10), &p, *(unsigned int*)(*(char**)(self + 0x10) + 0x3e8));
    func_002D55D0(*(void**)(self + 0x48), 0x3f);
    return 0;
}
