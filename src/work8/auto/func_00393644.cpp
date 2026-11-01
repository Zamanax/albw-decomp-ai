extern "C" void func_00393648();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00393644() { func_00393648(); }
