extern "C" void func_004A1520();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004A151C() { func_004A1520(); }
