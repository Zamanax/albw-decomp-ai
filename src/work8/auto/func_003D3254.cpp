extern "C" void func_003D3258();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003D3254() { func_003D3258(); }
