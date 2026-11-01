extern "C" void func_003674D0();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003674CC() { func_003674D0(); }
