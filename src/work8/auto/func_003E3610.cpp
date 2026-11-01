extern "C" void func_003E3614();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003E3610() { func_003E3614(); }
