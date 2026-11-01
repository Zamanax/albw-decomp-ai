extern "C" void func_003E31E8();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003E31E4() { func_003E31E8(); }
