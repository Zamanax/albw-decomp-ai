#include "../../work4/shared_include/cls_1DE.h"

struct HandleObjV : public HandleObjT {
    virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22();
    virtual bool v23(void* x, Vec3* p);
};
void func_004D80A4(Vec3* out, u32 angle, f32 len);

struct HeldOwner {
    char pad[0x48];
    Cls* m48;
    char pad4c[0x90 - 0x4c];
    Handle m90;
    void func_003B2808();
};

void HeldOwner::func_003B2808() {
    HandleObjT* o = DynamicCast<HandleObjT>(func_0052FBA0(&data_00706E20->handles, m90.v));
    if (isAliveObj(o)) {
        Vec3 v;
        v.set(0.0f, 0.0f, 0.0f);
        func_004D80A4(&v, m48->m3e8.v, 0.25f);
        v.y = 0.0f;
        HandleObjV* h = static_cast<HandleObjV*>(o);
        h->v23(m48->m2cc, &v);
        m90.reset();
    }
}
