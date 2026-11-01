extern "C" void func_00230958();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00230954() { func_00230958(); }
