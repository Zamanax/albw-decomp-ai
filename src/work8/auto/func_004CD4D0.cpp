extern "C" void func_004CD4D4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004CD4D0() { func_004CD4D4(); }
