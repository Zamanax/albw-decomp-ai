extern "C" void func_0019586C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00195868() { func_0019586C(); }
