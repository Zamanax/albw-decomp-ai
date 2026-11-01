extern "C" void func_0035D66C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0035D668() { func_0035D66C(); }
