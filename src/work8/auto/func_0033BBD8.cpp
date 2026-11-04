#include "../H2/range.h"
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
extern "C" void func_00665E08(void*, s32);
extern "C" void func_001507D8(void*, const sead::SafeString&, s32);
struct Pair {
    u32 cur;
    u32 max;
};
struct Act {
    u8 pad0[0x45c];
    u8 m45c;
    u8 pad45d[0x474 - 0x45d];
    Pair m474;
};
extern "C" void func_0033BBD8(Act* a) {
    Pair p = a->m474;
    if (p.cur >= p.max) {
        func_00665E08((char*)a + 0x40c, 5);
        return;
    }
    if (a->m45c) func_00665E08((char*)a + 0x40c, 1);
    Pair q = a->m474;
    if (q.cur < q.max) a->m474.cur = q.cur + 1;
    func_001507D8(a, sead::SafeString("SE_LightArrow_FLY"), 0);
}
