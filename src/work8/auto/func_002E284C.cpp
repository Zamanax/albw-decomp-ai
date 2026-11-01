typedef unsigned char u8; typedef unsigned int u32;
extern u8 ro_006DDE80[];
extern u8 ro_006F54BC[];
extern "C" void func_0010F1F8(void*);
extern "C" void* func_004A1520(void*);
void func_002E284C(char* self) {
    char* sub = self + 0x3c;
    *(void**)self = (void*)ro_006DDE80;
    *(void**)(self + 0x3c) = (void*)ro_006F54BC;
    if (*(u8*)(sub + 0x38)) {
        char* node = sub + 0x10;
        char* p = *(char**)(sub + 0x1c);
        if (p) {
            *(void**)(node + 0xc) = 0;
            func_0010F1F8(node);
            *(u32*)(p + 8) -= 1;
        }
        *(u8*)(sub + 0x38) = 0;
    }
    func_004A1520((char*)func_004A1520(sub) - 0x3c);
}
