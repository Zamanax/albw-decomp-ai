extern "C" void func_0020BE30();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0020BE2C() { func_0020BE30(); }
