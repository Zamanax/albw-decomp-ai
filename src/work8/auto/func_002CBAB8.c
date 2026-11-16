extern void func_0010B380(void* p, unsigned a, unsigned b, unsigned c);
extern char ro_0069F4F8[];
extern char ro_0069F4FA[];

struct Buf {
    int count;
    int cap;
    void** data;
};

static void pushPtr(struct Buf* b, void* v) {
    if (b->count < b->cap) {
        b->data[b->count] = v;
        b->count = b->count + 1;
    }
}

void func_002CBAB8(unsigned char* self) {
    func_0010B380(self + 0x9B0, 2, 0, 4);
    struct Buf* b = (struct Buf*)(self + 0x9B0);
    pushPtr(b, ro_0069F4F8);
    pushPtr(b, ro_0069F4FA);
}
