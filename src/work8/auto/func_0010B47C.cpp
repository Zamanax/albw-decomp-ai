extern "C" void func_0010B480();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0010B47C() { func_0010B480(); }
