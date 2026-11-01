extern "C" void func_002AF830();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002AF82C() { func_002AF830(); }
