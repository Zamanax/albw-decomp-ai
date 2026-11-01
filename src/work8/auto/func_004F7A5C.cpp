extern "C" void func_004F7A60();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004F7A5C() { func_004F7A60(); }
