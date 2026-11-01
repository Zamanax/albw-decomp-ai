extern "C" void func_001139FC();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_001139F8() { func_001139FC(); }
