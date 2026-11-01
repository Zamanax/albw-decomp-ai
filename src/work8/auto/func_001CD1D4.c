typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
extern void func_0037D414(void*);
__inline void setAB(void* s, u32 a, u32 b) { *(u8*)((char*)s + 0x425) = a; *(u8*)((char*)s + 0x426) = b; }
__inline void setC(void* s, u32 c) { *(u16*)((char*)s + 0x42c) = c; }
void func_001CD1D4(void* self) {
    func_0037D414(self);
    setAB(self, 1, 0);
    setC(self, 2);
}
