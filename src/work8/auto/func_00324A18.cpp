extern "C" void func_00324A1C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00324A18() { func_00324A1C(); }
