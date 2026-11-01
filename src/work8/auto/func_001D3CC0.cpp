extern "C" void func_001D3CC4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_001D3CC0() { func_001D3CC4(); }
