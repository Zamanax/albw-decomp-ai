extern "C" void func_00259550();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0025954C() { func_00259550(); }
