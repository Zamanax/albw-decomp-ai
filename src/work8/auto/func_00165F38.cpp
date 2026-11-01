extern "C" void func_00165F3C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00165F38() { func_00165F3C(); }
