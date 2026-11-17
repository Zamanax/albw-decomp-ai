typedef unsigned int u32;
typedef unsigned char u8;
struct EffRet12 { u32 a, b, c; };
extern struct EffRet12 func_004A1B9C(void*, const char*);
struct Obj { char pad0[0x344]; void* m344; char pad1[0x150]; u32 m498; u32 m49c; char pad2[3]; u8 m4a3; };
static inline void start(void* e, const char* n) { if (e != 0) { struct EffRet12 r = func_004A1B9C(e, n); } }
void func_00375288(struct Obj* p, u8 b, u32 v) {
  u8* bp = &p->m4a3;
  p->m49c = v;
  p->m498 = p->m49c;
  *bp = b;
  start(p->m344, "Warp");
}
