extern "C" void func_001507A8();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_001507A4() { func_001507A8(); }
