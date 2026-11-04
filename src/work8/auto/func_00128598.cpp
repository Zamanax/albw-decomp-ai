typedef unsigned int u32;
typedef int s32;
typedef short s16;

namespace sead {
class SafeString {
public:
    SafeString(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;
};
}

struct Actor;
s32 func_00588BE4(Actor* a);
void func_00150A84(Actor* a, const sead::SafeString& name, s32 v);
extern const s32 data_006939E0;

struct Sub500 { char p0[8]; s16 m8; };
struct Actor {
    char p0[0x500];
    Sub500 m500;
};

extern "C" void func_00128598(Actor* self) {
    if (self->m500.m8 <= 0) {
        if (func_00588BE4(self) == data_006939E0) {
            func_00150A84(self, sead::SafeString("SE_Chasupa_V_DIE"), 0);
        } else {
            func_00150A84(self, sead::SafeString("SE_Keese_V_DIE"), 0);
        }
    }
}
