extern "C" void func_0013ED4C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0013ED48() { func_0013ED4C(); }
