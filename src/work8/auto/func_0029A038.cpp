extern "C" void func_0029A03C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0029A038() { func_0029A03C(); }
