extern "C" void func_001047C8();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_001047C4() { func_001047C8(); }
