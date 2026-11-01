extern "C" void func_00172CC0();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00172CBC() { func_00172CC0(); }
