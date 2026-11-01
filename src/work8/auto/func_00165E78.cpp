extern "C" void func_00165E7C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00165E78() { func_00165E7C(); }
