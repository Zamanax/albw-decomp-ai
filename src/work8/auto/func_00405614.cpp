extern "C" void func_00405618();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00405614() { func_00405618(); }
