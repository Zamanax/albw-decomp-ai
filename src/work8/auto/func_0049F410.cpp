extern "C" void func_0049F414();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0049F410() { func_0049F414(); }
