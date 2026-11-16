typedef unsigned int u32;
typedef unsigned char u8;

extern char* data_007142C8;
extern void func_0012CE68(char* self);

void func_0046EB80(char* self) {
    u32 idx = ((u8*)self)[0x90];
    char** slots = (char**)(data_007142C8 + 0x90);
    char** p = idx < 4 ? slots + idx : slots;
    char* obj = *p;
    void (*fn)(char*) = *(void (**)(char*))(*(char**)obj + 0x34);
    fn(obj);
    ((u8*)obj)[0xe] = 0;
    ((u8*)obj)[0xd] = 0;
    func_0012CE68(self);
}
