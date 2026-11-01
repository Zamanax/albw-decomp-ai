extern "C" void func_0024DEB4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0024DEB0() { func_0024DEB4(); }
