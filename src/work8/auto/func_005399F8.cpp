typedef unsigned int u32;
typedef int s32;

struct SoundMgr;
extern SoundMgr* data_00711F50;

struct TmpBuf { char pad[0x64]; };

struct Obj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5(s32 id);
};

void func_0010A464(TmpBuf* t);
void func_00587EB4(SoundMgr* mgr, s32 id, s32 flag, TmpBuf* t);
void func_0025B66C(TmpBuf* t, float f);
void func_0025B84C(TmpBuf* t);

void func_005399F8(Obj* self, s32 id, s32 flag) {
    if (id == -1) return;
    if (flag != 0) {
        TmpBuf t;
        func_0010A464(&t);
        func_00587EB4(data_00711F50, id, flag, &t);
        func_0025B66C(&t, 0.4f);
        func_0025B84C(&t);
        return;
    }
    self->v5(id);
}
