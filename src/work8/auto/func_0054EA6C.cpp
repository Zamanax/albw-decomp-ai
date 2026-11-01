extern "C" void func_0054EA70();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0054EA6C() { func_0054EA70(); }
