void func_00384CA0(void*);
void func_00399A44(void*);
void func_00382A00(void*);
void func_003AF248(void*);
void func_003A2460(void*);
void func_00398A48(void*);
void func_003A38C8(void*);
void func_003BAE58(void*);
void func_00398164(void*);
void func_003AB160(void*);
void func_00397160(void*);
void func_0039917C(void*);
void func_003AFA60(void*);
void func_003BCBA4(void*);
void func_003831E4(void*);
void func_003A2FD4(void*, int);
void func_003AFDB4(void*);
void func_003BCCEC(void*);

void func_003A2ABC(char* self) {
    func_00384CA0(self + 0xc);
    func_00399A44(self + 0x1f0);
    func_00382A00(self + 0x2cc);
    func_003AF248(self + 0x30c);
    func_003A2460(self + 0x358);
    func_00398A48(self + 0x394);
    func_003A38C8(self + 0x414);
    func_003BAE58(self + 0x3d4);
    func_00398164(self + 0x454);
    func_003AB160(self + 0x554);
    func_00397160(self + 0x598);
    func_0039917C(self + 0x5e8);
    func_003AFA60(self + 0x6f8);
    func_003BCBA4(self + 0x834);
    func_003831E4(self + 0x870);
    func_003A2FD4(self, 1);
    {
        void* o = *(void**)(self + 4);
        if (o != 0) {
            void (*f)(void*) = *(void (**)(void*))(*(char**)o + 0xc);
            f(o);
        }
    }
    {
        void* o = *(void**)(self + 8);
        if (o != 0) {
            void (*f)(void*) = *(void (**)(void*))(*(char**)o + 0xc);
            f(o);
        }
    }
    char* p5 = self + 0x6f8;
    if (*(char**)(self + 4) != p5) func_003AFDB4(p5);
    char* p6 = self + 0x834;
    if (*(char**)(self + 4) != p6) func_003BCCEC(p6);
}
