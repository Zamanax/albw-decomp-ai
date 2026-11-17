extern unsigned char bss_0079CC98[];
extern unsigned char data_00701000[];
extern unsigned char data_00703000[];
extern unsigned func_00108630(void*, unsigned, unsigned);
extern void func_0010AC24(unsigned, unsigned);
extern void func_0010C0C0(void*);
extern void func_0010C160(void*);
extern unsigned func_003C7EEC(void*);

struct R26 { unsigned value; };
static inline void diag(unsigned result, unsigned pc) {
    struct R26 r = { result };
    unsigned s = r.value >> 31;
    if (s) func_0010AC24(result, pc);
}

unsigned func_003D2410(void) {
    unsigned short buf;
    unsigned result = func_00108630(&buf, 4, 0xd0000);
    diag(result, __current_pc());
    func_0010C0C0(bss_0079CC98);
    if ((int)(func_003C7EEC(data_00701000) & 0x80000000) < 0) {
        func_0010C160(bss_0079CC98);
        return 0;
    }
    unsigned lo = data_00703000[0x2c];
    unsigned hi = data_00703000[0x2d];
    func_0010C160(bss_0079CC98);
    unsigned v = lo;
    v |= hi << 8;
    return buf >= v;
}
