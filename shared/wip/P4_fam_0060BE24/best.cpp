typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef unsigned char u8;

#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

struct Vec3 { f32 x, y, z; };
struct Npc;
struct Actor;
struct Mdl;

extern "C" Vec3* func_00520FC0(Npc*);
extern "C" void func_00115C70(Vec3* out, const Vec3& a, const Vec3& b);
extern "C" s32 func_004904CC(f32, f32);
struct AngleT { s32 v; AngleT(s32 x) : v(x) {} };
extern "C" u32 func_0058E2B8(const AngleT&);
extern "C" Actor* func_00556068(void*);

struct Actor {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(Vec3*);
};

struct Mdl {
    u8 pad0[0x18];
    Mdl* m18;
};

struct Npc {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42();
    virtual void request(s32, s32);
    u8 pad4[0x3d0 - 4];
    Vec3 m3d0;
    f32 m3dc, m3e0, m3e4;
    s32 m3e8;
    u8 pad3ec[0x75c - 0x3ec];
    Mdl m75c;
    u8 pad778[0x7ec - 0x778];
    f32 m7ec_x;
    f32 m7f0;
    f32 m7ec_z;
    u8 pad7f8[0x818 - 0x7f8];
    s32 m818;
    u8 pad81c[0x853 - 0x81c];
    u8 m853, m854, m855;
    u8 pad856[0x858 - 0x856];
    u8 m858;
    u8 pad859[0x85d - 0x859];
    u8 m85d;
    u8 pad85e[0x861 - 0x85e];
    u8 m861;
    u8 pad862[0x8ac - 0x862];
    u32 m8ac;
    u8 pad8b0[0x988 - 0x8b0];
    u8 m988;
    void raise(f32 d) { m7f0 += d; }
    void bump(u8 s) { if (m988 == 0) { u8 v = 1; m988 = v; } }
    void run0(Vec3* tgt, u32 zero) {
        Vec3 pos = *func_00520FC0(this);
        Vec3 d;
        func_00115C70(&d, pos, m3d0);
        f32 x = d.x;
        m818 = func_004904CC(x, d.z);
        tgt->x = pos.x;
        tgt->y = pos.y;
        tgt->z = pos.z;
        for (s32 i = 0; i < 1; ++i) m7f0 += 1.0f;
        if (func_0058E2B8(AngleT(m3e8 - m818)) <= ((m8ac & 1) ? 0x15555555u : 0x071C71C7u))
            m861 = (u8)zero;
        else {
            Npc* q = this;
            q->request(m854, -1);
        }
    }
};

static Actor* owner(Npc* p) {
    Mdl* q = (Mdl*)((u8*)p + 0x75c);
    if (q) {
        Mdl* o = q->m18;
        if (o && o != q) return func_00556068(o);
    }
    return 0;
}

void func_0060BE24(Npc* p) {
    if ((p->m8ac & 0x10) || p->m858 == 1) {
        p->bump(1);
    }
    Vec3* tgt = (Vec3*)((u8*)p + 0x7ec);
    switch (p->m988) {
    case 0: {
        p->run0(tgt, 0);
        break;
    }    case 1:
        p->request(p->m855, -1);
        break;
    case 2: {
        if (owner(p)) {
            Mdl* q = (Mdl*)((u8*)p + 0x75c);
            Mdl* o = q->m18;
            if (o && o != q && func_00556068(o)) ((Actor*)o)->v8(tgt);
        }
        p->request(p->m853, -1);
        break;
    }
    }
    p->m3dc = 0.0f;
    p->m3e0 = 0.0f;
    p->m3e4 = 0.0f;
    p->m85d = 1;
    p->v38();
}
