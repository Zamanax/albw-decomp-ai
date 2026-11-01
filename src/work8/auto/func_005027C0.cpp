extern "C" void func_005027C4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_005027C0() { func_005027C4(); }
