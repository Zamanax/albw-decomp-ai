typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

struct Hdr {
  u32 m0;
  u16 m4;
  u8 pad6[2];
  u32 m8;
  u32 mc;
  u16 m10;
};

s32 func_003E6600(Hdr* self, u32 key, u32 v, u32 n) {
  if (self->m0 != key) return 0;
  if (self->m4 != 0xFEFF) return 0;
  if ((v >> 24) != (self->m8 >> 24)) return 0;
  u8 a = (u8)(v >> 16);
  u8 b = (u8)(self->m8 >> 16);
  if (a < b) return 0;
  if ((v & 0xff) > (self->m8 & 0xff)) return 0;
  if (self->mc < 0x14 + (n << 3)) return 0;
  return self->m10 >= n ? 1 : 0;
}
