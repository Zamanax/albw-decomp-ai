extern void* data_00711F50;
extern void* data_00712468;
extern void* data_00709DF8;
extern void func_00297448(void*, float, int);
extern void func_004EC074(void*, float, int);
extern void func_00297474(void*, float, int);
extern void func_004EAC54(void*, int);
extern void func_004EB9F4(void*);

void func_00259214(char* self) {
    func_00297448(data_00711F50, 0.0f, 0x1e);
    func_004EC074(data_00711F50, 0.0f, 0x1e);
    func_00297474(data_00711F50, 0.0f, 0x1e);
    signed char sys = *(signed char*)((char*)data_00712468 + 0x25);
    if (sys != 3) {
        char* g = (char*)data_00709DF8;
        if (g == 0 || sys == 2) {
            func_004EB9F4(data_00711F50);
        } else if (*(signed char*)(g + 0x48) == 8 || *(signed char*)(g + 0x48) == 0x26) {
            func_004EB9F4(data_00711F50);
        } else if (*(signed char*)(g + 0x18) == 8 || *(signed char*)(g + 0x18) == 0x26) {
            func_004EB9F4(data_00711F50);
        } else if (*(int*)(self + 0x3c) == 0x1a) {
            if (*(unsigned char*)((char*)data_00711F50 + 0x81) != 0) {
                func_004EB9F4(data_00711F50);
            }
        } else {
            func_004EAC54(data_00711F50, 1);
        }
    }
}
