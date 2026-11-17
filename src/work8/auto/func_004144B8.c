extern void func_003DD64C(void* d, void* buf, unsigned v, void* self, unsigned sz);

void func_004144B8(void* self, unsigned v, unsigned n, void* d) {
    unsigned char buf[0x1c];
    for (unsigned i = 0; i < n; i += 14) {
        func_003DD64C(d, buf, v, self, 14);
        d = (char*)d + 8;
    }
}
