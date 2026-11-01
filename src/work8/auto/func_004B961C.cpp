extern "C" void func_004B9620();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004B961C() { func_004B9620(); }
