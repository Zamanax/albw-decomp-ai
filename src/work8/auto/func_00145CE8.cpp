extern "C" void func_00145CEC();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00145CE8() { func_00145CEC(); }
