typedef unsigned int u32;
extern char* func_00498290(char* p);
extern char ro_006F7A94[];

void* func_004A0C0C(void* self) {
    char* p = (char*)self;
    *(char**)p = ro_006F7A94;
    p += 0x30;
    char* r = func_00498290(p);
    return r - 0x30;
}
