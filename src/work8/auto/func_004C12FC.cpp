extern "C" void func_004C1300();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004C12FC() { func_004C1300(); }
