extern "C" void func_0010E1CC();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0010E1C8() { func_0010E1CC(); }
