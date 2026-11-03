extern "C" void func_0010C7F8(void*, int, float);
struct Arr { unsigned int num; unsigned int cap; void** data; };
struct S { char pad[0x1c]; unsigned int m1C; char g[0x16c - 0x20]; Arr mArr; };
static void* at(Arr* a, unsigned int i) { if (i < a->num) return a->data[i]; return 0; }
extern "C" void func_00320EC4(S* p) {
    unsigned int n = p->m1C;
    for (unsigned int i = 0; i < n; i++) { Arr* a = &p->mArr; func_0010C7F8(at(a, i), 0, 1.0f); }
}
