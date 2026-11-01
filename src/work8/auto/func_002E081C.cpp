extern "C" void func_002E0820();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002E081C() { func_002E0820(); }
