extern "C" void func_00110388();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00110384() { func_00110388(); }
