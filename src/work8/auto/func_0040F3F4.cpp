extern "C" void func_0040F3F8();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0040F3F4() { func_0040F3F8(); }
