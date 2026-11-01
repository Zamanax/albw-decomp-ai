extern "C" void func_0017222C();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00172228() { func_0017222C(); }
