extern "C" void func_00446828();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00446824() { func_00446828(); }
