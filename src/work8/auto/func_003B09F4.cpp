extern "C" void func_003B09F8();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003B09F4() { func_003B09F8(); }
