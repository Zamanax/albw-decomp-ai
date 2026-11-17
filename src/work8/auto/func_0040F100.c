extern char ro_006F04CC[];
extern void* func_0040E208(void*);
extern void* func_0041B1B8(void*);
extern void* func_00416E34(void*);
extern void func_0067F924(void*);
extern void* func_00100118(void*, void (*)(void*), unsigned int, unsigned int);

void* func_0040F100(void* self, void* p) {
    char* b = (char*)func_0040E208(self);
    *(void**)b = (void*)ro_006F04CC;
    char* c = (char*)func_00416E34((char*)func_0041B1B8(b + 0x114) + 0x1c98) - 0x1dac;
    *(void**)(c + 0x29e4) = p;
    c = (char*)func_00100118(c + 0x29e8, func_0067F924, 0x10, 4) - 0x29e8;
    *(unsigned char*)(c + 0x2c2e) = 0;
    *(void**)(c + 0x2c30) = 0;
    *(void**)(c + 0x2c34) = 0;
    return c;
}
