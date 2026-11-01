extern "C" void func_00417D28();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00417D24() { func_00417D28(); }
