typedef unsigned int u32;
typedef int s32;

extern s32 func_00588BE4(void*);
extern u32 func_005811E8(void*);
extern void func_004A3788(void*);
extern void func_004F8638(void*, s32);
extern char ro_006939BC[];

void func_0037F1C0(void* self) {
    if (func_00588BE4(self) == *(u32*)ro_006939BC) {
        if (func_005811E8((char*)self + 0x800 + 0x344)) func_004A3788((char*)self + 0x800 + 0x344);
        if (func_005811E8((char*)self + 0x800 + 0x33c)) func_004A3788((char*)self + 0x800 + 0x33c);
        if (func_005811E8((char*)self + 0x800 + 0x354)) func_004A3788((char*)self + 0x800 + 0x354);
        if (func_005811E8((char*)self + 0x800 + 0x34c)) func_004A3788((char*)self + 0x800 + 0x34c);
    }
    *((char*)self + 0xb2c) = 0;
    func_004F8638(self, -1);
}
