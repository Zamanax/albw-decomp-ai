extern "C" void func_003E3F04();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003E3F00() { func_003E3F04(); }
