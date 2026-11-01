extern "C" void func_003AAE3C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003AAE38() { func_003AAE3C(); }
