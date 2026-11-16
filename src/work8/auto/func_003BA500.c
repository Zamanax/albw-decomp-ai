extern unsigned int data_0070FB60;
extern unsigned int data_00709F30;
extern unsigned int func_0055696C(unsigned int, unsigned int);
extern void func_004C6654(unsigned int, unsigned int);
extern void func_00383DF8(void*, unsigned int);

void func_003BA500(void* p1)
{
    char* self = (char*)p1;
    unsigned char one = 1;
    unsigned int lvl;
    void* obj;

    lvl = func_0055696C(data_0070FB60, 3);
    if (lvl >= 3) {
        func_004C6654(data_00709F30, 8);
        func_004C6654(data_00709F30, 9);
    } else {
        func_004C6654(data_00709F30, 8);
    }

    obj = *(void**)(*(char**)(self + 0x48) + 0xbcc);
    if (obj != 0) {
        (*(void (**)(void*))(*(char**)obj + 0x14))(obj);
    }

    *(unsigned char*)(*(char**)(self + 0x48) + 0x936) = one;
    *(unsigned short*)(self + 0x90) = 0;
    func_00383DF8(*(char**)(self + 0x48) + 0x8c0, 0);
    self[0x62] = 0;
    self[0x63] = 0;
    (*(void (**)(void*))(*(char**)self + 0xfc))(self);
    self[0x9c] = one;
}
