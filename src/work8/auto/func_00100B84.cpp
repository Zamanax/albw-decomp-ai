extern "C" void svc_ExitProcess_00100B88();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00100B84() { svc_ExitProcess_00100B88(); }
