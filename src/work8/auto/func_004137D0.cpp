extern "C" void func_004137D4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004137D0() { func_004137D4(); }
