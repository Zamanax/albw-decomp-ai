extern void func_0058FA08(void*);

struct S {
    void* a;
    void* b;
    void* c;
};

void func_0048C22C(struct S* self) {
    if (self->c) {
        func_0058FA08(self->c);
        self->c = 0;
        self->a = 0;
        self->b = 0;
    }
}
