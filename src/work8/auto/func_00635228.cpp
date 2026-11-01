extern "C" void func_0063522C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00635228() { func_0063522C(); }
