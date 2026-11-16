extern void func_00490CD0(void* self, unsigned char* out);

struct Obj {
    void* p0;
    unsigned int f4;
    int f8;
    int f12;
    unsigned char flag16;
};

void func_00490F34(struct Obj* self) {
    unsigned char buf[0x20];
    if (self->p0 != 0) {
        self->flag16 = 0;
        if (self->f12 > self->f8) {
            do {
                func_00490CD0(self, buf);
            } while (self->f12 > self->f8);
        }
    }
}
