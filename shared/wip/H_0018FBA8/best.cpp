// 0x18FBA8  Hookshot::Hookshot(ActorParam*)
#include "actor_types.h"

void* func_00435714(s32* kind);
void func_004356B4(Obj435714* o);
void func_004EDEA0(void* o, u32* handle);
void func_0014EB8C(void* o, void* a, u32 b, void* c, s32 d, void* e, u32 f);
u32 func_0054DDF4(Hookshot* o, bool b);
u32 func_0054D89C(Hookshot* o, s32 b);
void* func_002C2D00(void* p);
void func_00533400(void* a, void* b);
void* func_005532D8(void* a, s32 b, s32 c);
void func_00659688(void* a, s32 b);
void func_00151148(void* a, s32 b);
void func_0018FAD0(Hookshot* o);
void func_0018CFAC(Hookshot* o);
void func_0018E15C(Hookshot* o);
void func_004A9120(void* a, void* b);
void func_004A8BFC(void* a, void* b, s32 c);
void func_00556CB8(void* a);
void func_00115154(f32* s, f32* c, u32 angle);
void* func_0052FBA0(u32 handle);

struct Obj70FB60 { char pad[0x1c]; Vec3 m1c; };
extern Obj70FB60* data_0070FB60;
struct Obj709DF8 { char pad[0x18]; s8 m18; };
extern Obj709DF8* data_00709DF8;
struct Obj709D28;
extern Obj709D28* data_00709D28;
struct Obj711010 { char pad[0x10]; u32 m10; };
extern Obj711010* data_00711010;
struct Obj706E20;
extern Obj706E20* data_00706E20;
struct Obj7266C0;
extern Obj7266C0* data_007266C0;
extern u32 data_007266C4;
struct Obj6C57E0;
extern Obj6C57E0* data_006C57E0;

struct ActorParam {
    char pad44[0x44];
    f32 m44;
    char pad48[0x4c - 0x48];
    u32 m4c;
};

static HFunc const sFuncs[23] = {
    &Hookshot::v19, &Hookshot::v20,
    &Hookshot::st0Enter, &Hookshot::st0Exec, &Hookshot::st0Exit,
    &Hookshot::st1Enter, &Hookshot::st1Exec, &Hookshot::st1Exit,
    &Hookshot::st2Enter, &Hookshot::st2Exec, &Hookshot::st2Exit,
    &Hookshot::st3Enter, &Hookshot::st3Exec, &Hookshot::st3Exit,
    &Hookshot::st4Enter, &Hookshot::st4Exec, &Hookshot::st4Exit,
    &Hookshot::st5Enter, &Hookshot::st5Exec, &Hookshot::st5Exit,
    &Hookshot::st6Enter, &Hookshot::st6Exec, &Hookshot::st6Exit,
};

static HFunc const sHookEnd[4] = {
    &Hookshot::st5Enter, &Hookshot::st5Exec, &Hookshot::st5Exit, &Hookshot::st6Enter,
};

Hookshot::Hookshot(ActorParam* p)
    : ActorBase(p),
      m40c(this, sFuncs[0]),
      m41c(this, sFuncs[1]),
      m434(0),
      m438(),
      mStateMgr(),
      m4e4(0x19),
      m4e8(0),
      m4f8(0.0f),
      m4fc(0),
      m520(0),
      m528(0),
      m52c(0),
      m530(0),
      m534(0),
      m538(),
      m548(),
      m55a(0),
      m55d(0),
      m560(0),
      m561(0),
      m562(0),
      m564(0.0f, 0.0f, 0.0f),
      m56c(0.0f),
      m57c(0) {
    s32 n = (s32)p->m44;
    bool big = n >= 10;
    bool odd = (n % 10) != 0;
    m55e = odd;
    f32 k = odd ? 0.7f : 0.4f;
    f32 f = k * 4.5454545f;
    s32 cnt = (s32)f;
    if ((f32)cnt != f) {
        if (0.0f <= f) cnt++;
    }
    Heap* heap;
    m42c = (void**)new (heap) u32[cnt];
    m430 = (Sub438**)new (heap) Sub438[cnt];

    Vec3 target;
    void* other = 0;
    if (m57c) {
        other = func_0052FBA0(m57c);
        static const TypeInfoRoot sTi;
        if (other && !((ActorBaseA*)other)->checkDerived(&sTi)) other = 0;
        if (!other) {
            m2d7 = 1;
            return;
        }
        target = ((ActorBase*)other)->m3d0;
        m562 = 1;
    } else {
        target = data_0070FB60->m1c;
    }

    f32 y = target.y + 0.8f;
    f32 s, c;
    func_00115154(&s, &c, m3e8);
    Vec3 d(s * 0.65f, 0.0f, c * 0.65f);
    m3d0.setAdd(m3d0, d);
    m4cc = m3d0;
    m4cc.y = y;
    m4d8 = m4cc;

    s32 kind = 6;
    for (s32 i = 0; i < cnt; i++) {
        Obj435714* o = (Obj435714*)func_00435714(&kind);
        m42c[i] = o;
        o->m4 = m4cc;
        o->m58 = 0.22f;
        func_004356B4(o);
    }

    s8 mode = data_00709DF8->m18;
    if (mode == 0xe || mode == 0x10 || mode == 0x13 || mode == 0x14) {
        s32 kind2 = 6;
        Obj435714* o = (Obj435714*)func_00435714(&kind2);
        m434 = o;
        o->m4 = m3d0;
        o->m58 = 0.22f;
        func_004356B4(o);
    }

    m4c0 = m3d0;
    m4ec.setSub(m4c0, target);

    mStateMgr.mNum = 8;
    mStateMgr.mNameCount = 8;
    mStateMgr.mNames = new FixedSafeString24[8];
    mStateMgr.mOwner = this;
    mStateMgr.mEnter = new HFunc[8];
    mStateMgr.mExec = new HFunc[8];
    mStateMgr.mExit = new HFunc[8];
    for (s32 i = 0; i < 8; i++) {
        mStateMgr.mEnter[i] = sFuncs[21];
        mStateMgr.mExec[i] = sFuncs[21];
    }
    m354 = &mStateMgr;
    m35a = 8;

    mStateMgr.setStateName(0, sead::SafeString("cState_Release"));
    mStateMgr.mEnter[0] = sFuncs[2];
    mStateMgr.mExec[0] = sFuncs[3];
    mStateMgr.mExit[0] = sFuncs[4];
    mStateMgr.setStateName(1, sead::SafeString("cState_Return"));
    mStateMgr.mEnter[1] = sFuncs[5];
    mStateMgr.mExec[1] = sFuncs[6];
    mStateMgr.mExit[1] = sFuncs[7];
    mStateMgr.setStateName(2, sead::SafeString("cState_ReturnPutAway"));
    mStateMgr.mEnter[2] = sFuncs[8];
    mStateMgr.mExec[2] = sFuncs[9];
    mStateMgr.mExit[2] = sFuncs[10];
    mStateMgr.setStateName(3, sead::SafeString("cState_Stick"));
    mStateMgr.mEnter[3] = sFuncs[11];
    mStateMgr.mExec[3] = sFuncs[12];
    mStateMgr.mExit[3] = sFuncs[13];
    mStateMgr.setStateName(4, sead::SafeString("cState_StickLast"));
    mStateMgr.mEnter[4] = sFuncs[14];
    mStateMgr.mExec[4] = sFuncs[15];
    mStateMgr.mExit[4] = sFuncs[16];
    mStateMgr.setStateName(5, sead::SafeString("cState_StickPutAway"));
    mStateMgr.mEnter[5] = sFuncs[17];
    mStateMgr.mExec[5] = sFuncs[18];
    mStateMgr.mExit[5] = sFuncs[19];
    mStateMgr.setStateName(6, sead::SafeString("cState_HookSwitchPull"));
    mStateMgr.mEnter[6] = sFuncs[20];
    mStateMgr.mExec[6] = sFuncs[21];
    mStateMgr.mExit[6] = sFuncs[22];
    mStateMgr.setStateName(7, sead::SafeString("cState_HookEnd"));
    mStateMgr.mEnter[7] = sHookEnd[0];
    mStateMgr.mExec[7] = sHookEnd[1];
    mStateMgr.mExit[7] = sFuncs[4];

    for (s32 i = 0; i < cnt; i++) {
        m430[i]->m10 = m42c[i];
        u32 h = m2cc;
        func_004EDEA0(&m430[i], &h);
    }
    if (m434) {
        m438.m10 = m434;
        u32 h = m2cc;
        func_004EDEA0(&m438, &h);
    }

    u32 v = func_0054DDF4(this, m55e != 0);
    m3a0 = v;
    m3a4 = v;
    m538 = Delegate(this, sFuncs[19]);
    for (s32 i = 0; i < cnt; i++) {
        func_0014EB8C(&m430[i], m42c[i], func_0054DDF4(this, m55e != 0), &m2cc,
                      (s16)m54, &m538, 0xffff);
    }
    if (m434) {
        m548 = Delegate(this, sFuncs[20]);
        func_0014EB8C(&m438, m434, func_0054DDF4(this, m55e != 0), &m2cc,
                      (s16)m54, &m548, 0xffff);
    }

    if (m562) {
        for (s32 i = 0; i < cnt; i++) {
            func_004A9120(data_00709D28, &m430[i]);
            func_004A8BFC(data_00709D28, &m430[i], 3);
            m430[i]->m32 = 0x920;
            m430[i]->m22 = 5;
        }
    }
    for (s32 i = 0; i < cnt; i++) {
        ((Obj435714*)m42c[i])->m2c |= 8;
        ((Obj435714*)m42c[i])->m2c |= 0x80000;
    }

    f32 sc, cc;
    func_00115154(&sc, &cc, m3e8);
    f32 k2 = m55e ? 0.7f : 0.4f;
    m3dc = sc * k2;
    m3e0 = 0.0f;
    m3e4 = cc * k2;

    if (m57c) {
        void* mgr = (void*)data_00711010->m10;
        s32 sel = big ? 0 : (m55e ? 2 : 1);
        void* q = func_005532D8(mgr, 4, sel);
        func_00533400(q, &sead::SafeString("Hook"));
        m528 = func_002C2D00(&q);
        m530 = (void*)func_0054D89C(this, 0);
        func_00533400(q, &sead::SafeString("Hook"));
        s32 n2 = m55e ? 0xc : 9;
        m52c = new u32[n2];
        for (s32 i = 0; i < n2; i++) {
            ((u32*)m52c)[i] = (u32)func_002C2D00(&q);
            if (m534) ((u32*)m534)[i] = func_0054D89C(this, 1);
        }
    }
    func_00659688(&mStateMgr, 0);
    func_0018FAD0(this);
    func_0018CFAC(this);
    func_0018E15C(this);
    func_00151148(m530, 0);
}
