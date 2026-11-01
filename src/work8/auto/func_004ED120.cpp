extern "C" void func_004ED124();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004ED120() { func_004ED124(); }
