#include "albw_types.h"

// 0x936 byte flag on the child object reached through p->m48.
struct Child3B39 {
    char pad936[0x936];
    u8 m936;
    void set936(u8 v) { m936 = v; }
};

// Slots 0..0x137 of the object's vtable; the tail-called dispatch is slot 78 (0x138).
struct Virtual138 {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
    virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
    virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
    virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
    virtual void v76(); virtual void v77(); virtual void v78(s32, bool);
};

struct Obj3B39 : Virtual138 {
    char pad4C[0x48 - 4];
    Child3B39* child;
};

// 0x001E6CE8 is a `bx lr` no-op (it sits in ~15 vtables); the original call to it was
// inlined away by armlink, which is why the target has a `mov r0, r0` at +0x8.
extern void func_001E6CE8(Obj3B39*);

void func_003B39BC(Obj3B39* p) {
    func_001E6CE8(p);
    p->child->set936(1);
    p->v78(0, true);
}
