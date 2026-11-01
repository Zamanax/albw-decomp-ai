extern "C" void func_00325CF4();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00325CF0() { func_00325CF4(); }
