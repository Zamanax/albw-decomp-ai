extern "C" void func_0048D1B0();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0048D1AC() { func_0048D1B0(); }
