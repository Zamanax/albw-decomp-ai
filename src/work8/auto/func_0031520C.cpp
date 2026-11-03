typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned char u8;
struct Mgr709;
extern Mgr709* data_00709D28;
struct Item49c { char pad[0x10]; };
void func_004A9120(Mgr709* m, Item49c* it);
void func_004A8BFC(Mgr709* m, Item49c* it, s32 n);
struct Obj39 {
    char pad0[0x49c];
    Item49c m49c;
    char pad4ac[0x4be - 0x4ac];
    u8 m4be;
    char pad4bf[0x4ce - 0x4bf];
    u16 m4ce;
    void f();
};
void Obj39::f() {
    func_004A9120(data_00709D28, &m49c);
    func_004A8BFC(data_00709D28, &m49c, 3);
    m4ce = 0x920;
    m4be = 5;
}
