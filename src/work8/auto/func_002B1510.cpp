extern "C" void func_002B1514();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002B1510() { func_002B1514(); }
