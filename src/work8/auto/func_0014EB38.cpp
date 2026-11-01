extern "C" void func_0014EB3C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0014EB38() { func_0014EB3C(); }
