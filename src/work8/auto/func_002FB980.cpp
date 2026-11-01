extern "C" void func_002FB984();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002FB980() { func_002FB984(); }
