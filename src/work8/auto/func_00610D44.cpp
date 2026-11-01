extern "C" void func_00610D48();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00610D44() { func_00610D48(); }
