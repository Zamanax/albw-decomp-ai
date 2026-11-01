extern "C" void func_0015BB18();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0015BB14() { func_0015BB18(); }
