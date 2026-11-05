typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;
extern void* data_00711F50;
struct EffRet2{u32 a,b;};
extern EffRet2 func_004A1B9C(void*,const char*);
extern "C" void func_00587F74(void*, void*, void*);

#include "sead_string.h"
namespace sead {

}
struct ActiveOwner30{u32 pad0;s32 count;u32 pad8,id;u8 gap10[0x270];u8 active;};
struct TrackedObject30{u8 pad0[0x1c];u32 id;ActiveOwner30*owner;u32 ownerId;u8 pad28[0x14];u32 flags;void activate(u8 value){if(owner&&ownerId==owner->id&&owner->count>0)owner->active=value;}};
struct TrackedHandle30{TrackedObject30*ptr;u32 id;};
struct Sub400 {u8 pad0[0x48];TrackedHandle30 handle;};
struct Self19B{u8 pad0[0x344];void* m344;u8 pad348[0x400-0x348];Sub400 sub;};
inline void startAnim(void*p,const char*n){if(p)func_004A1B9C(p,n);}

extern "C" void func_001C722C(Self19B* a) {
    TrackedHandle30* h = &a->sub.handle;
    TrackedObject30* o = h->ptr;
    if (o && o->id == h->id) {
        o->activate(1);
        o->flags = (o->flags & ~4u) | 8u;
    }
    startAnim(a->m344, "Go");
    const sead::SafeString& snd = sead::SafeString("SE_S_WARP_HOLE_SAGE_OUT_START");
    func_00587F74(data_00711F50, (void*)&snd, 0);
}
