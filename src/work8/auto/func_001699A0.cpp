extern "C" void func_00567588(void* a, void* b, void* c, void* d, int e, float f);
extern "C" void func_0069021C(void* a, void* b, void* c, void* d, float f);

static inline float clampF(float v, float lo, float hi) {
    if (v < lo) v = lo;
    else if (v > hi) v = hi;
    return v;
}

extern "C" void func_001699A0(void* self, void** h, int flag, float v) {
    char* o = (char*)*h;
    char* p = (char*)h + 8;
    float s = clampF(v, 0.0f, *(float*)(o + 8) - 1.0f);
    if (*(unsigned char*)(o + 5) != 1) return;
    if (flag) {
        func_00567588(o, self, p, (char*)h + 0x10, flag, s);
        return;
    }
    func_0069021C(o, self, p, (char*)h + 0x10, s);
}
