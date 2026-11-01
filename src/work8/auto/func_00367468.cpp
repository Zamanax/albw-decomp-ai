extern "C" void func_0036746C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00367468() { func_0036746C(); }
