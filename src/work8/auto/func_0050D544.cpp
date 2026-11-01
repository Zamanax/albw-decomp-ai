extern "C" void func_0050D548();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0050D544() { func_0050D548(); }
