typedef float f32;
extern "C" f32 func_0058A404(void*);
extern "C" int func_00548E78(void* p, int a, int b) {
    f32 t = func_0058A404(p);
    f32 one = 1.0f;
    f32 inv = one - t;
    f32 u = one - inv;
    f32 fa = (f32)a;
    f32 fb = (f32)b;
    return (int)(u * fa + inv * fb);
}
