extern "C" void func_0024A228();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_0024A224() { func_0024A228(); }
