extern "C" void func_00100D88();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00100D84() { func_00100D88(); }
