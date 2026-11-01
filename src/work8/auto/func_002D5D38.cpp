extern "C" void func_002D5D3C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002D5D38() { func_002D5D3C(); }
