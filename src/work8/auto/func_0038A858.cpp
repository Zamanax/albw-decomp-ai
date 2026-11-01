extern "C" void func_0038A85C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0038A858() { func_0038A85C(); }
