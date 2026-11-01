extern "C" void func_00616A18();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00616A14() { func_00616A18(); }
