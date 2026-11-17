#include "vec3.h"
extern "C" void func_004356B4(void*);
struct Obj { unsigned int h; Vec3 v; };
extern "C" void func_004C0AD0(void* a0, Obj* obj, const Vec3* src, const Vec3* b) {
  if (obj == 0) return;
  Vec3 t = *src;
  t += *b;
  Vec3& d = obj->v;
  d.x = t.x;
  d.y = t.y;
  d.z = t.z;
  func_004356B4(obj);
}
