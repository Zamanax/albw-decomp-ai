extern "C" void func_0048AC64();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0048AC60() { func_0048AC64(); }
