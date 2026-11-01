extern "C" void func_0054E650();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0054E64C() { func_0054E650(); }
