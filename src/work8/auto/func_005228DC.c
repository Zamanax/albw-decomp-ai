typedef unsigned int u32;
typedef unsigned char u8;

extern u32* data_007124F0;

u32 func_005228DC(u8* p, u32 v)
{
  u32 n = *(u32*)(p + 0x18);
  if (n == 0) return 0;
  if (v != 0) {
    u32 i = n - 1;
    u32 e = (n > i) ? ((u32*)*(u32*)(p + 0x20))[i] : 0;
    if (e != v) return 0;
  }
  {
    u32 idx = n - 1;
    u32 e2 = (n > idx) ? ((u32*)*(u32*)(p + 0x20))[idx] : 0;
    u8 b = *(u8*)(e2 + 0x70);
    u32 t = b * 0x19;
    char* base = (char*)data_007124F0;
    base += 0x10;
    u32* g = (u32*)(base + (t << 4));
    u32 f = g[7] & 1;
    return f != 0;
  }
}
