extern "C" void func_004D0A60();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004D0A5C() { func_004D0A60(); }
