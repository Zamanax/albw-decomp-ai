typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef struct Ctrl231L { s16 index; s16 kind; s32 pad; void* owner; } Ctrl231L;
typedef struct Obj1994 { u8 p0[0x1c]; void* f1c; u8 p20[0x68 - 0x20]; Ctrl231L c68; u8 p74[0x79 - 0x74]; u8 f79; } Obj1994;
extern void func_00231448(Ctrl231L*);
extern void func_002317C0(Ctrl231L*, float);
void func_001994AC(Obj1994* p) {
  if (p->f79 & 2) {
    func_00231448(&p->c68);
    p->c68.owner = p->f1c;
    Ctrl231L* t0 = &p->c68;
    t0->kind = 4;
    t0->index = 0;
    func_002317C0(t0, 1.0f);
    p->f79 &= ~2;
  }
}
