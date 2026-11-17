extern void func_006177C0(void* self, int a, int b);

static __forceinline float clampF(float v, float lo, float hi) {
    if (v < lo) v = lo;
    else if (v > hi) v = hi;
    return v;
}
__declspec(noinline) void func_001CB798(void* self, float v) {
    v = clampF(v, 0.01f, 1.0f);
    v = v * 1.15f;
    *(float*)((char*)self + 0x830) = v;
    char* p = *(char**)((char*)self + 0x7a0);
    unsigned f = *(unsigned*)(p + 0x164);
    f |= 0x40000000u;
    *(unsigned*)(p + 0x164) = f;
    *(float*)(p + 0x74) = v;
    *(float*)(p + 0x78) = v;
    *(float*)(p + 0x7c) = v;
}

void func_001CB7F8(void* self) {
    int n = *(int*)((char*)self + 0x960);
    float v = 1.0f - (float)n * 0.066666667f;
    func_001CB798(self, v);
    if (n < 15) return;
    func_001CB798(self, 0.01f);
    func_006177C0(self, 6, 0);
}
