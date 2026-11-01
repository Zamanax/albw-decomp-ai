extern "C" void func_0010478C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00104788() { func_0010478C(); }
