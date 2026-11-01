extern "C" void func_00498290();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0049828C() { func_00498290(); }
