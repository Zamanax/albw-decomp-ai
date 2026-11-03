typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_006F762C[];
extern char ro_006F761C[];
extern char data_007165A0[];
extern unsigned func_0010CEE0(unsigned, unsigned, unsigned);
extern unsigned func_0010DA7C(unsigned, unsigned, unsigned);

unsigned func_0049E74C(unsigned heap)
{
  unsigned h901, r0, obj, inner, disp, head;
  if (*(unsigned *)((char *)data_007165A0) == 0) {
    obj = func_0010CEE0(0x3c, heap, 4);
    inner = obj + 4;
    r0 = inner;
    if (inner != 0) {
      h901 = heap;
      disp = func_0010DA7C(inner, h901, 3);
      *(unsigned *)((char *)disp) = (unsigned)ro_006F761C;
      r0 = disp;
    }
    *(unsigned *)((char *)data_007165A0 + 4) = r0;
    if (obj != 0) {
      *(unsigned *)((char *)obj + 0x14) = 0;
      *(unsigned *)((char *)obj) = (unsigned)ro_006F762C;
      *(unsigned *)((char *)obj + 0x18) = 0;
      *(unsigned *)((char *)obj + 0x1C) = 0;
      *(unsigned *)((char *)obj + 0x20) = 0;
      head = obj + 0x24;
      *(unsigned *)((char *)obj + 0x2C) = 0;
      *(unsigned *)((char *)obj + 0x28) = head;
      *(unsigned *)((char *)obj + 0x34) = 0;
      *(unsigned *)((char *)obj + 0x24) = head;
      *(unsigned char *)((char *)obj + 0x38) = 0;
      *(unsigned char *)((char *)obj + 0x39) = 0;
      *(unsigned char *)((char *)obj + 0x3A) = 0;
      *(unsigned char *)((char *)obj + 0x3B) = 0;
      *(unsigned *)((char *)obj + 0x30) = 4;
    }
    *(unsigned *)((char *)data_007165A0) = obj;
  }
  return *(unsigned *)((char *)data_007165A0);
}
