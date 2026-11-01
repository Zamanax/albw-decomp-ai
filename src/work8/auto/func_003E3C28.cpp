extern "C" void func_003E3C2C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003E3C28() { func_003E3C2C(); }
