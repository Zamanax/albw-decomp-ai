extern "C" void func_0048E0B0();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0048E0AC() { func_0048E0B0(); }
