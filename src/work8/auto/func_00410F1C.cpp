extern "C" void func_00410F20();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00410F1C() { func_00410F20(); }
