extern "C" void func_002518A8();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002518A4() { func_002518A8(); }
