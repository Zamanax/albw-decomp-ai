extern "C" void func_0038F454();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0038F450() { func_0038F454(); }
