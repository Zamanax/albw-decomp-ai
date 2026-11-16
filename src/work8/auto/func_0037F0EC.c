typedef unsigned int u32;
extern char ro_006F5988[];
extern u32 func_005811E8(void*);
extern void func_00150CD0(void*, u32*, void*, u32, u32);
extern void func_004F68AC(void*, u32);

void func_0037F0EC(char* a0, u32 a1)
{
  u32 b = a1;
  u32 c = func_005811E8(a0 + 0xb3c);
  u32 vt = (u32)ro_006F5988;
  if (c) {
    u32 lv[2];
    u32* q = lv;
    lv[0] = vt;
    lv[1] = (u32)"SE_IronSoldier_FIRE";
    func_00150CD0(a0, q, a0 + 0xa90, 0, 0);
  } else if (func_005811E8(a0 + 0xb4c)) {
    u32 lv[2];
    u32* q = lv;
    lv[0] = vt;
    lv[1] = (u32)"SE_IronSoldier_FIRE_OFF";
    func_00150CD0(a0, q, a0 + 0xa90, 0, 0);
  }
  func_004F68AC(a0, b);
}
