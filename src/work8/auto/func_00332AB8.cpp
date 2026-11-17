typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern void* data_00706E20;
u32 func_0052FBA0(void*, u32);
void func_00230610(void*, u32);

void func_00332AB8(char* self) {
    if (self[0x4bc] != 0) return;
    char* p = self + 0x400;
    u32* arr = (u32*)(p + 0xfc);
    s32 i = 0;
    s32 n = 4;
    do {
        if (arr[i]) {
            void* a = (void*)func_0052FBA0((char*)data_00706E20 + 0x3dbbc, arr[i]);
            u32 h2 = arr[i];
            func_00230610(*(void**)(self + 0x488), h2);
            if (*(u16*)((char*)a + 0x2c) == 1) self[0x519] = 1;
        }
        i++;
    } while (i != n);
    if (*(u16*)(self + 0x2c) == 1) self[0x519] = 1;
}
