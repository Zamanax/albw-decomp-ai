extern "C" void func_005106DC();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_005106D8() { func_005106DC(); }
