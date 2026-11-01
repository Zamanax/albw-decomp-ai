extern "C" void func_0041B8B4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0041B8B0() { func_0041B8B4(); }
