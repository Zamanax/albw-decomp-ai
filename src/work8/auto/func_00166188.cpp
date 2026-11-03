typedef unsigned int u32;
typedef int s32;
extern "C" void func_002E1B70(void*);
extern "C" void func_0010F1F8(void*);
static void recycle5(char* head, char*& p) {
    while (p != head) {
        char* next = *(char**)(p + 4);
        func_0010F1F8(p);
        *(u32*)(head + 8) -= 1;
        s32 v = *(u32*)(head + 0xc);
        p -= 4;
        *(u32*)p = v;
        *(char**)(head + 0xc) = p;
        p = next;
    }
}
void func_00166188(char* self) {
    func_002E1B70(self + 0xac);
    char* head = self + 0x34;
    char*& pr = *(char**)(self + 0x38);
    char* p = pr;
    recycle5(head, p);
}
