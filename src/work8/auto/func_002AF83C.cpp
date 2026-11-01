extern "C" void func_002AF840();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002AF83C() { func_002AF840(); }
