typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Obj { char pad0[0x134]; float f134; } Obj;
typedef struct Ent { Obj* obj; u8 flags; u8 pad5[3]; float f8; } Ent;
typedef struct O { Ent ents[14]; u8 count; } O;

void func_004FCEDC(O* p, float v) {
  u32 i = 0;
  O * t1 = p;
  while (i < t1->count) {
    if (4 & p->ents[i].flags) {
      O * t0 = p;
      Obj* o = t0->ents[i].obj;
      if (o) {
        t0->ents[i].f8 = o->f134 = v;
      }
    }
    i++;
  }
}
