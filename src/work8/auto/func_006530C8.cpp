extern "C" void func_006530CC();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_006530C8() { func_006530CC(); }
