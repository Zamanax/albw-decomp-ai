extern "C" void func_004EDD04();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004EDD00() { func_004EDD04(); }
