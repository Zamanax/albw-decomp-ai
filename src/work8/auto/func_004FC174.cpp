extern "C" void func_004FC178();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_004FC174() { func_004FC178(); }
