extern "C" void func_004F68AC();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004F68A8() { func_004F68AC(); }
