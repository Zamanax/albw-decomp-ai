extern "C" void func_0048FBB4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0048FBB0() { func_0048FBB4(); }
