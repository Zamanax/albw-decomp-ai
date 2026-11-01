extern "C" void func_003E35E0();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003E35DC() { func_003E35E0(); }
