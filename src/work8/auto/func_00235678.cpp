typedef unsigned int u32;
typedef int s32;
extern "C" void func_004CEA18(void*, s32, s32);
extern "C" void func_002356D4(void*, s32);
struct Ent { char pad0[8]; void* obj; char pad1[0x104 - 12]; };
struct Owner {
    char pad0[0x630];
    u32 count;
    Ent* arr;
    Ent& at(u32 i) { if (i < count) return arr[i]; return arr[0]; }
};
extern "C" void func_00235678(Owner* p, s32 value) {
    u32 v = value;
    void* o = p->at(v).obj;
    if (o) {
        func_004CEA18(o, 1, 0);
        func_004CEA18(o, 0, 1);
    }
    func_002356D4(p, value);
}
