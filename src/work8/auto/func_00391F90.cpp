extern "C" void func_00391F94();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00391F90() { func_00391F94(); }
