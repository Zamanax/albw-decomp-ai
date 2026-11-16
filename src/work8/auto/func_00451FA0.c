extern void func_001B6DE0(void*);

void func_00451FA0(void* self) {
    func_001B6DE0(self);
    unsigned char* o = *(unsigned char**)((unsigned char*)self + 0x44);
    if (o != 0) {
        if (o[0xd] != 0 || o[0xe] != 0) {
            void (*fp)(void*) = *(void (**)(void*))((char*)*(void**)o + 0x34);
            unsigned char* q = o;
            fp(o);
            q[0xe] = 0;
            q[0xd] = 0;
        }
    }
    *(void**)((unsigned char*)self + 0x44) = 0;
}
