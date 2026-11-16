extern void func_0028D580(char* anim, int id, int a, int b, int blend);

int func_002902CC(void* self, unsigned char v) {
    short st = *(short*)((char*)self + 0x42);
    if (st == 0 || st == 1) {
        char* o = *(char**)((char*)self + 0x10);
        if (*(int*)(o + 0x620) == 0) {
            *((unsigned char*)self + 0xc5) = 1;
            *((unsigned char*)self + 0xc6) = v;
            char* a = *(char**)((char*)self + 0x18);
            func_0028D580(a + 0x3c, 0x87, 1, 1, 6);
        }
    }
    return 1;
}
