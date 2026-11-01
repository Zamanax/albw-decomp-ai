extern "C" void func_00625CAC();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00625CA8() { func_00625CAC(); }
