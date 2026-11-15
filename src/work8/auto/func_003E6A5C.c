extern void func_001164F4(void* p, unsigned int n);

struct Heap {
    char* buf;
    unsigned int off;
};

void func_003E6A5C(struct Heap* self, unsigned int align) {
    unsigned int mask = align - 1;
    unsigned int off = self->off;
    unsigned int end = (off + mask) & ~mask;
    func_001164F4(self->buf + off, end - off);
    self->off = end;
}
