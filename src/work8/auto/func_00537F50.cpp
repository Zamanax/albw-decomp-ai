extern "C" void func_00537F54();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00537F50() { func_00537F54(); }
