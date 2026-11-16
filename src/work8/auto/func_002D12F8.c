struct Obj12F8 {
    unsigned char pad0[0x10];
    void* m10;
    unsigned int m14;
    unsigned int m18;
    unsigned int m1c;
    unsigned int m20;
    unsigned int m24;
    unsigned int m28;
    unsigned char m2c;
    unsigned char m2d;
    unsigned int m30;
};

extern unsigned int func_0053F758(void*, void*);

void func_002D12F8(struct Obj12F8* self) {
    unsigned int* p = &self->m20;
    *p = self->m14;
    p[1] = self->m18;
    p[2] = self->m1c;
    self->m2d = self->m2c;
    if (self->m30 != 0) {
        self->m30 = self->m30 - 1;
    } else {
        self->m2c = func_0053F758(self->m10, &self->m14);
    }
}
