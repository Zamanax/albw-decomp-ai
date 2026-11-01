extern "C" void func_00100C94();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00100C90() { func_00100C94(); }
