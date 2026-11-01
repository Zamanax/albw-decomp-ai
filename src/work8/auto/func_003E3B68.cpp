extern "C" void func_003E3B6C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003E3B68() { func_003E3B6C(); }
