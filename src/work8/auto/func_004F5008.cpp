extern "C" void func_004F500C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004F5008() { func_004F500C(); }
