extern int func_00104800(void);
extern void func_0010C1B8(void);
extern int func_00103CBC(unsigned int);
extern int func_00104868(void*, unsigned int, int, int);

int func_0010AA40(int* self, unsigned int value) {
    unsigned int s = (unsigned int)func_00104800() >> 31;
    if (s) func_0010C1B8();
    if (*self != 0) return 0xd8a103f9;
    int r = func_00104868(self, value, func_00103CBC(value), 0);
    int m = r & (int)0x80000000u;
    if (m < 0) return 0xd92103fb;
    return r;
}
