extern "C" void func_0048CF54();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0048CF50() { func_0048CF54(); }
