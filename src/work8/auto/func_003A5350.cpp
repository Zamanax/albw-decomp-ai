extern "C" void func_003A5354();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003A5350() { func_003A5354(); }
