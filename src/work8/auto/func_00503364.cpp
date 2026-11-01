extern "C" void func_00503368();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00503364() { func_00503368(); }
