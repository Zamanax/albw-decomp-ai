extern "C" void func_0049A024();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0049A020() { func_0049A024(); }
