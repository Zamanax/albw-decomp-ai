extern "C" void func_0068B074();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0068B070() { func_0068B074(); }
