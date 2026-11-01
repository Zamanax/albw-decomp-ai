extern "C" void func_00165D88();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00165D84() { func_00165D88(); }
