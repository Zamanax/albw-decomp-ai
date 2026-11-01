extern "C" void func_003EA528();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003EA524() { func_003EA528(); }
