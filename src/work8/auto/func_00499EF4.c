typedef unsigned char u8;
typedef unsigned int u32;

extern void func_00490A18(void* a, void* b);
extern void func_00490AB8(void* a, void* b);

void func_00499EF4(u8* self, u32 idx, void* v)
{
  switch (idx) {
  case 0: func_00490A18(self + 0x70, v); break;
  case 1: func_00490A18(self + 0xc0, v); break;
  case 2: func_00490A18(self + 0x160, v); break;
  case 3: func_00490A18(self + 0x1b0, v); break;
  case 4: func_00490A18(self + 0x200, v); break;
  case 5: func_00490A18(self + 0x2a0, v); break;
  case 6: func_00490A18(self + 0x2f0, v); break;
  case 7: func_00490A18(self + 0x340, v); break;
  case 8: {
    u8 f = self[0x390];
    if (f == 0) func_00490AB8(self + 0x160, v);
    else if (f == 1) func_00490AB8(self + 0x2a0, v);
    break;
  }
  case 9: {
    u8 f = self[0x391];
    if (f == 0) func_00490AB8(self + 0x1b0, v);
    else if (f == 1) func_00490AB8(self + 0x2f0, v);
    break;
  }
  case 10: {
    u8 f = self[0x391];
    if (f == 0) func_00490AB8(self + 0x200, v);
    else if (f == 1) func_00490AB8(self + 0x340, v);
    break;
  }
  default: break;
  }
}
