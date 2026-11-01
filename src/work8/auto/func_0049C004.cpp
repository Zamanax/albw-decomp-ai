extern "C" void func_0049C008();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0049C004() { func_0049C008(); }
