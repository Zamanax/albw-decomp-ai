extern "C" void func_003F6F84();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_003F6F80() { func_003F6F84(); }
