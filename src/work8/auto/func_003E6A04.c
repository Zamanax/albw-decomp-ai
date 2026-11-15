extern void func_001163A0(void*, const void*, unsigned int);

void func_003E6A04(unsigned int* self, const void* src, unsigned int n) {
    func_001163A0((void*)(self[0] + self[1]), src, n);
    self[1] += n;
}
