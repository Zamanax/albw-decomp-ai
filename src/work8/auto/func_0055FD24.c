typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

extern void* data_0070B728;
extern void* data_0070FB60;
extern u32 func_0055F308(void* self, s32 a, void* b);

u32 func_0055FD24(void* self, s32 a, void* b) {
  char* o = (char*)self;
  if (a == 5 || a == 10) {
    if (*(u32*)((char*)data_0070B728 + 0x44) != 0) return 0;
    void* r = *(void**)(o + 0x48);
    if (*(u8*)((char*)r + 0x936) != 2) {
      char* pl = (char*)data_0070FB60;
      float d = *(float*)((char*)*(void**)(pl + 0x1c) + 4) - *(float*)((char*)r + 0x3d4);
      d = (d > 0.0f) ? d : -d;
      if (d > 3.0f) return 0;
    }
    void* x = *(void**)((char*)r + 0xbcc);
    void** vt = *(void***)x;
    if (((u32(*)(void*))vt[7])(x) == 0) return 0;
  }
  return func_0055F308(self, a, b);
}
