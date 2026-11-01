extern "C" void func_004BDCEC();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004BDCE8() { func_004BDCEC(); }
