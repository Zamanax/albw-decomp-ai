extern "C" void func_004ECDE8();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004ECDE4() { func_004ECDE8(); }
