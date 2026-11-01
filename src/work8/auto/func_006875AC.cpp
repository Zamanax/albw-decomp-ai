extern "C" void func_006875B0();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_006875AC() { func_006875B0(); }
