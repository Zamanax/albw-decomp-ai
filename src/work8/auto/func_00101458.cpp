extern "C" void func_0010145C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00101458() { func_0010145C(); }
