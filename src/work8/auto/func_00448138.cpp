typedef unsigned char u8;
typedef signed int s32;
typedef float f32;

namespace sead {
template <typename T>
class SafeStringBase {
public:
    SafeStringBase(const T* s) : mStringTop(const_cast<T*>(s)) {}
    virtual ~SafeStringBase() {}
    virtual void assureTerminationImpl_() const {}
    T* mStringTop;
};
typedef SafeStringBase<char> SafeString;
}

struct SEHandle {
    u8 buf[0x60];
};

extern const char ro_006A5008[];   // "SE_S_MAP_MOVE"

extern void func_0010A464(SEHandle* h);
extern void func_0025B84C(SEHandle* h);
extern bool func_00539200(SEHandle* h);
extern void func_0025B838(SEHandle* h, f32 v, s32 a);
extern void func_0025B694(SEHandle* h, f32 v);
extern void func_0025B788(SEHandle* h, s32 a);
extern void func_00533048(void* self, const sead::SafeString& name, SEHandle* h);

static inline f32 clampf(f32 v, f32 lo, f32 hi) {
    if (v < lo) v = lo;
    else if (v > hi) v = hi;
    return v;
}

void func_00448138(void* self, f32 s, s32 flag) {
    if (s > 0.05f) {
        SEHandle h;
        func_0010A464(&h);
        func_00533048(self, sead::SafeString(ro_006A5008), &h);
        if (func_00539200(&h)) {
            f32 v = clampf(s * 0.1f, 0.3f, 1.0f);
            func_0025B838(&h, v, 0);
            func_0025B694(&h, 1.0f + s * 0.5f);
            if (flag != 0 && s < 3.0f) func_0025B788(&h, 3);
        }
        func_0025B84C(&h);
    }
}
