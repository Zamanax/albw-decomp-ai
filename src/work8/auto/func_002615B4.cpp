extern "C" void func_002615B8();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002615B4() { func_002615B8(); }
