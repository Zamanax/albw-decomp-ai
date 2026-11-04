#include "../nm3/ds2.h"

class SafeString_006F5988 {
public:
    SafeString_006F5988(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;
};
extern "C" {
void* func_00584C14(void* m, const SafeString_006F5988& name);
void func_004CEA18(void* m, bool on, void* n);
}
extern void func_004FC07C(void*, int, int, int);

struct TimerA27 { u32 cur; u32 max; f32 rate;
    void start(u32 n) { f32 r = 1.0f / n; max = n; rate = r; cur = 0; }
};
struct Obj22BCB8 {
    char pad0[0x3dc];
    f32 m3DC, m3E0, m3E4;
    char pad3e8[0x40c - 0x3e8];
    void* m40c;
    char pad410[0xa70 - 0x410];
    TimerA27 mTimer;
};

void func_0022BCB8(Obj22BCB8* self) {
    self->m3DC = 0.0f;
    self->m3E0 = 0.0f;
    self->m3E4 = 0.0f;
    func_004FC07C(self, 0, -1, 0);
    self->mTimer.start(200);
    void* n = func_00584C14(self->m40c, SafeString_006F5988("Leg_front"));
    func_004CEA18(self->m40c, false, n);
}
