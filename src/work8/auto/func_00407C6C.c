typedef int s32;
typedef unsigned char u8;

struct Ctx {
    s32 m00;
    u8 pad04[0x0C];
    u8* m10;
    u8 pad14[0x1C];
    s32 m30;
    s32 m34;
};

void func_00407C6C(struct Ctx* self, s32 a) {
    s32 t = self->m34;
    s32 v;
    if (t < a) {
        v = t;
    } else {
        v = (a < 0) ? 0 : a;
    }
    self->m30 = v;
    for (;;) {
        if (self->m00 <= self->m30) {
            break;
        }
        u8* obj = self->m10 - 0x104;
        void (*fp)(void*) = (void (*)(void*))(*(void***)obj)[4];
        fp(obj);
    }
}
