extern "C" void func_00617370();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0061736C() { func_00617370(); }
