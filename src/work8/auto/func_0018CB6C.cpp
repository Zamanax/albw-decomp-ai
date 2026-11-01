extern "C" void func_0018CB70();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0018CB6C() { func_0018CB70(); }
