extern "C" void func_00261560();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0026155C() { func_00261560(); }
