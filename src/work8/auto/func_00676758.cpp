#include "../../work7/gpt28/range.h"
struct Mutex76 { u32 w0; u32 owner; u32 count; };
struct Obj76 { char pad[0x58]; Mutex76 mutex; };
struct Wrap76 { u32 w0; Obj76* obj; };
extern void func_0010C0C0(Mutex76*);
extern void func_0010C160(Mutex76*);
extern void func_003D306C(Obj76*, u32);
struct Lk76 { Mutex76* m; Lk76(Mutex76* p):m(p){func_0010C0C0(m);} ~Lk76(){func_0010C160(m);} };
void func_00676758(Wrap76* p, u32 a) {
    Obj76* o = p->obj;
    Lk76 lk(&o->mutex);
    func_003D306C(o, a);
}
