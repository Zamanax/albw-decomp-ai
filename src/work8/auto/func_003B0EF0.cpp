extern "C" void func_003B0EF4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003B0EF0() { func_003B0EF4(); }
