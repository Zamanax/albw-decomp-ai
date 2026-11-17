typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
extern void func_002AFEF0(void*,u32,u32,f32,u32,u32);
void func_002AE550(void* p){
    u8* a = *(u8**)((u8*)p+0x34) + 0x700;
    u16 v = *(u16*)(a+0x84);
    if (v == 0) { v = *(u16*)(a+0x82); *(u16*)(a+0x84) = v; }
    u8* b = *(u8**)((u8*)p+0x34) + 0x700;
    u32 w = *(u16*)(b+0x84);
    func_002AFEF0(p,0,w,0.0f,1,0);


}
