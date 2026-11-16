#include "vec3.h"
extern char data_00725974[];
extern char ro_006C88BC[];
extern char* func_00230740(char*, char*, unsigned, unsigned, unsigned);
extern char* func_002E1BB4(char*, unsigned);
unsigned func_001663BC(char* a0, unsigned a1, unsigned a2, unsigned a3, unsigned a4)
{
  char* p;
  char* t;
  Vec3* d;
  p = func_00230740(a0, data_00725974, a2, a3, a4);
  *(char**)p = ro_006C88BC;
  t = func_002E1BB4(p + 0xac, 0) - 0xac;
  *(unsigned*)(t + 0xc0) = 0;
  *(unsigned*)(t + 0xc4) = 0;
  *(unsigned*)(t + 0xc8) = 0;
  *(unsigned*)(t + 0xcc) = 0;
  *(unsigned*)(t + 0xd0) = 0;
  *(unsigned*)(t + 0xd4) = 0;
  *(unsigned*)(t + 0xd8) = 0;
  *(unsigned*)(t + 0xdc) = 0;
  *(unsigned*)(t + 0xe0) = 0;
  *(unsigned*)(t + 0xe4) = 0;
  *(unsigned*)(t + 0xe8) = 0;
  *(unsigned short*)(t + 0xec) = 0;
  *(float*)(t + 0xf0) = 0.0f;
  *(float*)(t + 0xf4) = 0.0f;
  *(unsigned char*)(t + 0xf8) = 0;
  *(unsigned char*)(t + 0xf9) = 0;
  *(unsigned char*)(t + 0xfa) = 0;
  *(unsigned char*)(t + 0xfb) = 1;
  Vec3 c;
  c.set(-1.0f, 0.0f, -1.0f);
  d = (Vec3*)(t + 0xfc);
  d->x = c.x;
  d->y = c.y;
  *(float*)(t + 0x104) = c.z;
  *(unsigned char*)(t + 0x10) = 1;
  return (unsigned)t;
}
