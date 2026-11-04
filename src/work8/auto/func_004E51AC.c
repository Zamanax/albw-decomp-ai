struct Vec3 { float x, y, z; };
extern void func_00169A80(int c);
extern void func_00168E9C(int c, int id, int z);
extern void func_004D8AEC(int o, int a, int b);
extern void func_00115D70(struct Vec3* out, struct Vec3* a, float s);
extern void func_004CEAF0(int m);
extern void func_001512E8(int m);
extern void func_001511F0(int m);

void func_004E51AC(int p) {
  int iVar1;
  struct Vec3 v;
  func_00169A80(*(int*)(p + 0x47c));
  func_00168E9C(*(int*)(p + 0x47c), *(int*)(p + 0x478), 0);
  func_00169A80(*(int*)(p + 0x480));
  func_00168E9C(*(int*)(p + 0x480), *(int*)(p + 0x478), 0);
  iVar1 = *(int*)(p + 0x478);
  *(unsigned int*)(iVar1 + 0x164) = *(unsigned int*)(iVar1 + 0x164) | 0x40000000;
  func_004D8AEC(iVar1 + 0x80, *(int*)(p + 0x3e8), p + 0x3d0);
  v = *(struct Vec3*)(p + 0x4e0);
  { struct Vec3* pv = &v; func_00115D70(pv, pv, *(float*)(*(int*)(*(int*)(p + 0x2d0) + 0x14))); }
  iVar1 = *(int*)(p + 0x478);
  *(unsigned int*)(iVar1 + 0x164) = *(unsigned int*)(iVar1 + 0x164) | 0x40000000;
  *(unsigned int*)(iVar1 + 0x74) = *(unsigned int*)&v.x;
  *(unsigned int*)(iVar1 + 0x78) = *(unsigned int*)&v.y;
  *(unsigned int*)(iVar1 + 0x7c) = *(unsigned int*)&v.z;
  func_004CEAF0(*(int*)(p + 0x478));
  func_001512E8(*(int*)(p + 0x4cc));
  func_001511F0(*(int*)(p + 0x4cc));
}
