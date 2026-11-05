// 0x412BB4: function-local static `Obj` with out-of-line ctor and dtor.
// Guard byte data_0071649C; object bss_007A3778; the guard calls are __cxa_guard_acquire
// (func_00100174) / __cxa_guard_release and the atexit registration is compiler-generated.
typedef unsigned char u8;
struct Obj {
    Obj();     // ctor func_00412FD4
    ~Obj();    // dtor func_006766F4 (registered with atexit; dso func_00100000)
    u8 p0[0x18e];
};
Obj* func_00412BB4() {
    static Obj obj;
    return &obj;
}
