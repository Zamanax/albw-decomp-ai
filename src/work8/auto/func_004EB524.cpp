#include "../../work7/ds6/ds6.h"

struct S4EB524 { char _pad[0x4c]; };
struct Obj4EB524 {
    char _pad[0x4c];
    void* m4c;
    void* m50;
};

void func_00689024(void* p);
u32 func_0053900C(void* p, void* q, u32 a);
void func_00296D28(void* p, void* q);
void func_004EB570(void* p, void* q);

void func_004EB524(Obj4EB524* self, u32 a) {
    S4EB524 s;
    func_00689024(&s);
    if (func_0053900C(self->m50, &s, a) != 0) {
        S4EB524* ps = &s;
        func_00296D28(self->m4c, ps);
        func_004EB570(self->m50, ps);
    }
}
