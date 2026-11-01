extern "C" void func_00629E78();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00629E74() { func_00629E78(); }
