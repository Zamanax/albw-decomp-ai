extern "C" void func_002E0510();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002E050C() { func_002E0510(); }
