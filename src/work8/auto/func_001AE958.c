extern void func_0065AD50(void*, int);
void func_001AE958(char* self) {
    if (*(unsigned char*)(self + 0x908)) {
        func_0065AD50(self + 0x90C, 9);
        return;
    }
    int t = *(unsigned char*)(*(char**)(self + 0x510) + 5);
    switch (t) {
    case 0:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
        func_0065AD50(self + 0x90C, 2);
        return;
    default:
        break;
    }
    *(unsigned char*)(self + 0x908) = 1;
    char* s = self;
    func_0065AD50(s + 0x90C, 9);
    *(int*)(s + 0x9D4) = 0;
}
