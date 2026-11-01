extern "C" void func_0023DCD8();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0023DCD4() { func_0023DCD8(); }
