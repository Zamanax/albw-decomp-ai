extern int func_00522828(void*, int);
extern int func_0058DC40(void*);
extern void func_0051B220(void*);
extern void func_0066BFFC(void*, int);
extern void* data_0070B850;
extern void* data_007142C8;
void func_00423958(void* p) {
    if (func_00522828(data_0070B850, 0) != 0) {
        if (func_0058DC40(data_007142C8) == 0) {
                        int* q = (int*)((char*)data_0070B850 + 0x10);
            if (*q >= 0x42c40000) {
                void* e = *(void**)((char*)data_007142C8 + 0xe8);
                if (e != 0) {
                    *(short*)((char*)e + 0x122) = 0x78;
                }
                func_0066BFFC((char*)p + 0x38, 2);
            }
        } else {
            func_0051B220(data_007142C8);
            func_0066BFFC((char*)p + 0x38, 5);
        }
    }
}
