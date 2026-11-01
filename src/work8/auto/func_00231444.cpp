extern "C" void func_00231448();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00231444() { func_00231448(); }
