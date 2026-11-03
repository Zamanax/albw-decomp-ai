typedef unsigned char u8; typedef unsigned short u16; typedef int s32; typedef unsigned int u32;
struct Object4E86 { char pad0[0x427]; u8 f427; char pad428[0x42c - 0x428]; u16 f42c; char pad42e[0x4d4 - 0x42e]; void* model; void* child; void run(); };
extern void func_004CF478(void*, bool, s32);
extern void func_00151148(void*, bool);
void Object4E86::run() {
    bool visible = true;
    bool other = visible;
    f427 = 0;
    func_004CF478(model, visible, 0);
    func_00151148(child, other);
    f42c = 0;
}
