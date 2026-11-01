extern "C" void func_00521064();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00521060() { func_00521064(); }
