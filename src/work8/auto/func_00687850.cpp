extern "C" void func_00687854();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00687850() { func_00687854(); }
