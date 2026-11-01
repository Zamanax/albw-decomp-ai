extern "C" void func_001891A0();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0018919C() { func_001891A0(); }
