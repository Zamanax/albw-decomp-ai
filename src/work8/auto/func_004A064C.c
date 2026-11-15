typedef unsigned char u8;

extern char ro_006F7A20[];
extern u8 data_00715164[];
extern void func_004A05A0(void* self);

void* func_004A064C(char* self) {
    char* p = self;
    *(float*)(p + 4) = 3.40282347e+38f;
    *(float*)(p + 8) = 3.40282347e+38f;
    *(float*)(p + 0xc) = -3.40282347e+38f;
    *(float*)(p + 0x10) = -3.40282347e+38f;
    *(char**)self = ro_006F7A20;
    *(u8*)(self + 0x14) = *data_00715164;
    func_004A05A0(self);
    return self;
}
