typedef unsigned char u8;
typedef unsigned int u32;

extern "C" char ro_006F78DC[];
extern "C" void func_0049D83C(void* self, u32 a);
extern "C" void func_0049FCE8(void* list);
extern "C" void func_0010F1F8(void* node);
extern "C" void func_004A1520(void* self);

struct Lst { void* prev; void* next; u32 count; };
struct Link { void* prev; void* next; u32 data; Lst* owner; };
struct Elem { u8 pad0[0x10]; u32 m10; };
struct Obj {
    void* vt;
    u8 p04[0x10 - 0x04];
    u8 m10[4];
    Elem* m14;
    u8 p18[0x34 - 0x18];
    Link link;
    u8 p44[0x5c - 0x44];
    void* m5c;
    u8 m60;
};

extern "C" void func_0049FAD8(Obj* self) {
    void* o = self->m5c;
    *(void**)self = ro_006F78DC;
    if (o != 0) {
        for (;;) {
            Elem* e = self->m14;
            if (e == 0) break;
            func_0049D83C(self->m5c, e->m10);
        }
    }
    self->m60 = 7;
    func_0049FCE8(self->m10);
    Link* lk = &self->link;
    Lst* l = self->link.owner;
    if (l != 0) {
        lk->owner = 0;
        func_0010F1F8(lk);
        --l->count;
    }
    func_004A1520(self);
}
