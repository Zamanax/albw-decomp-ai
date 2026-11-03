typedef unsigned int u32;
typedef unsigned char u8;
extern void* data_00711F50;
extern "C" void func_001C6FA8(void*);
extern "C" void func_00587F74(void*, void*, void*);
namespace sead {
struct SafeString {
    SafeString(const char* s) : text(s) {}
    virtual void assureTerminationImpl_() const;
    const char* text;
};
}
extern "C" void func_001C6E20(void* self) {
    u32 z = 0;
    u32 a = 60;
    u8* s = (u8*)self;
    u8* p = s + 0x400;
    u8* q = p + 0x38;
    *(u32*)(s + 0x43c) = a;
    *(float*)(q + 8) = 0.016666668f;
    *(u32*)(s + 0x438) = z;
    s[0x444] = 1;
    func_001C6FA8(self);
    const sead::SafeString& snd = sead::SafeString("SE_S_WARP_HOLE_APPEAR_SAGE_OUT");
    func_00587F74(data_00711F50, (void*)&snd, 0);
}
