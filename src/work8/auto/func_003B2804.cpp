extern "C" void func_003B2808();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003B2804() { func_003B2808(); }
