extern "C" void func_001510A4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_001510A0() { func_001510A4(); }
