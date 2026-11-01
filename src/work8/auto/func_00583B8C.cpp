extern "C" void func_00583B90();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00583B8C() { func_00583B90(); }
