extern "C" void func_003D25A4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003D25A0() { func_003D25A4(); }
