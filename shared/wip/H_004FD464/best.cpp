// 0x004FD464  EnemyBase::EnemyBase(EnemyArg* arg, EnemyParam* param)
#include "actor_types.h"

extern const Vec3 data_007A9260;   // sead::Vector3f::zero (bss, dyn-init)
extern const Vec3 data_007A9254;
extern u8 data_0070A5A4;
extern u32 data_0070A5AC;
struct G09DF8 {
    char pad[0x18];
    s8 m18;
};
extern G09DF8* data_00709DF8;

u8* func_004FA000(u32 a);
u32 func_0014E428(EnemyBase* self, u32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_004F9A2C(EnemyBase* self, void* p);
s32 func_005330BC(u32 v, void* p);
bool func_0054DD54(void* p, s32 i);
void* func_0054DD3C(void* p, s32 i);
u32 func_0054D89C(EnemyBase* self, s32 i);
void func_004FC798(Sub5A8* self, u32 v, u8* flags, f32 f);



EnemyBase::EnemyBase(EnemyArg* arg, EnemyParam* param)
    : ActorBase(arg),
      m40c(0), m410(0), m414(0), m418(0), m41c(0),
      m420(new (nt) X00E()), m424(0),
      m428(0), m42c(0), m430(0), m434(0),
      m438(new (nt) X10E()),
      m43c(new (nt) X20E()),
      m440(&m524), m444(&m534), m448(&m544),
      m44c(data_007A9260), m458(data_007A9254), m464(data_007A9260), m470(data_007A9254),
      m47c(data_007A9260), m488(data_007A9254), m494(data_007A9260), m4a0(data_007A9254),
      m4ac(0), m4b0(0), m4b4(0), m4b5(0),
      m4b8(data_007A9260), m4c4(1.0f), m4c8(1.0f), m4cc(1.0f),
      m4d0(data_007A9260), m4dc(8), m4e0(0), m4e4(data_007A9254),
      m4f0(1.0f), m4f4(1.0f), m4f8(1.0f),
      m4fc(0), m500(0), m504(0),
      m508(4), m50a(4), m50c(4), m50e(4),
      m510(new (nt) X30E(this)),
      m514(0, DlgFn()), m524(0, DlgFn()), m534(0, DlgFn()), m544(0, DlgFn()),
      m554(0, DlgFn()),
      m564(0.0f, 0.0f, 0.0f), m570(0.0f, 0.0f, 0.0f), m57c(0.0f), m580(0.0f),
      m584(0x1f08), m588(0x36), m58c(0xddf),
      m590(data_007A9260), m59c(0x1f390003), m5a0(0x3000), m5a4(m5a0),
      m768(0), m76c(0),
      m770(data_007A9260),
      m77c(1), m77d(-1), m77e(-1), m77f(0), m780(-1),
      m782(0x5a), m784(0), m786(0xffff), m788(0xffff),
      m798(1.2f), m79c(0), m7a0(0), m7a4(0), m7a8(data_007A9260),
      m7fc(0),
      m800(0), m804(0), m808(0), m80c(0), m810(0), m814(0), m818(0), m81c(0), m820(0),
      m824(0xff), m825(0xff), m826(0xff), m827(0xff),
      m828(0), m829(0), m82a(0),
      m82c(data_007A9260), m838(0), m83c(data_007A9260),
      m848(0), m849(0), m84a(0), m84c(0.0f),
      m850(2), m851(data_0070A5A4), m852(0), m853(0), m854(0.0f),
      m858(1), m859(0), m85a(0), m85b(0),
      m85c(0), m860(0), m864(1.0f), m868(0), m86c(0), m870(1.0f),
      m874(0x80), m875(0x80), m876(0x80), m877(0x80),
      m878(data_0070A5AC),
      m87c(0xa), m87d(0x14), m87e(0x28), m87f(0xa), m880(0xf), m881(5), m882(0),
      m884(&m884), m888(&m884), m88c(0), m890(0x28),
      m894(0), m895(0), m896(1), m897(0), m898(0.0f),
      m89c(0), m89d(0), m89e(0), m89f(0),
      m8a0(0), m8a4(0), m8a8(data_007A9260),
      m8b4(0), m8b5(0), m8b6(0), m8b7(1), m8b8(0) {
    m851 = *func_004FA000(0);
    m3cc = 1;
    m4cc = 1.0f;
    for (s32 i = 0; i < 7; ++i) {
        m5a8.v[i].clear();
        m5a8.list[i] = 0;
        m5a8.w[i].v = 0;
        m5a8.x[i].v = 0;
    }
    m5a8.c0 = m5a8.c1 = m5a8.c2 = m5a8.c3 = 0;

    if (!(param->m0 & 1)) {
        s32 k = param->mC;
        if (k < 0) k = func_005330BC(m2d0->m1c8[param->m8], &param->m18);
        m4e0 = m2d0->m1c8[param->m8];
        m40c = func_0014E428(this, param->m4 | 1, param->m8, k, 1, 0, 0);
        u8 c = (param->m44 & 0xff) | 4;
        func_004FC798(&m5a8, m40c, &c, -1.0f);
        m59c |= 0x400;
    }

    if ((s32)(param->m0 << 30) >= 0) func_004F9A2C(this, &param->m10);

    m554.mObj = this;
    m554.mFp = &EnemyBase::func_004F4A68;
    m3ec = &m554;

    if ((s32)(param->m0 << 29) >= 0) {
        s32 idx = 0;
        if (m2d0 && func_0054DD54(&m2d0->m18, idx) && func_0054DD3C(&m2d0->m18, idx) &&
            (m41c = func_0054D89C(this, idx)) != 0) {
            m5a8.addUnique((void*)m41c);
        }
    }

    if (m3a4) {
        u16 t = *(u16*)((u8*)m3a4 + 2);
        m50a = t;
        m508 = t;
    }

    G09DF8* g = data_00709DF8;
    if (g) {
        s8 v = g->m18;
        if (v == 0x14) m8b5 = 1;
        else if (v == 0xb) m8b8 = 1;
    }
}
