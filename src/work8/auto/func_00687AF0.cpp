extern "C" void func_00687AF4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00687AF0() { func_00687AF4(); }
