extern "C" void func_00108634();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00108630() { func_00108634(); }
