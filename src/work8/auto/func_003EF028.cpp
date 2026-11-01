extern "C" void func_003EF02C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003EF028() { func_003EF02C(); }
