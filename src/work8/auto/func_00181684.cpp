#include "albw_types.h"
#include "timer.h"

struct Obj181684 {
    char pad0[0x3dc];
    f32 m3DC, m3E0, m3E4;
    char pad3e8[0x9a4 - 0x3e8];
    Timer mTimer;
};

void func_00181684(Obj181684* self) {
    self->m3DC = 0.0f;
    f32* q = &self->m3E4;
    *q = 0.0f;
    self->m3E0 = 0.1f;
    void (*fp)(Obj181684*, s32, s32) = *(void (**)(Obj181684*, s32, s32))((char*)(*(void**)self) + 0xac);
    fp(self, 7, -1);
    self->mTimer.start(5);
}
