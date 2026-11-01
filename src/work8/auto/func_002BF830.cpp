extern "C" void func_002BF834();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002BF830() { func_002BF834(); }
