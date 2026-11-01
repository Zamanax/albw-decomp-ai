extern "C" void func_00104944();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00104940() { func_00104944(); }
