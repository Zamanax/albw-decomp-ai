extern "C" void func_0048A134();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0048A130() { func_0048A134(); }
