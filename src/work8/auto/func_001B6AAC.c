extern int func_00532C2C(void*);
extern void* func_001B6AFC(void*);

void* func_001B6AAC(char* p) {
    if (((unsigned char*)p)[0x9d] & 2) {
        if (func_00532C2C(p + 0x20) < 0x10) {
            if ((func_00532C2C(p + 0x20) & 3) == 0) {
                void** vt = *(void***)p;
                ((void (*)(void*))vt[15])(p);
            }
        }
    }
    return func_001B6AFC(p);
}
